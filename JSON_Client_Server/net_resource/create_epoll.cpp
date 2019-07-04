#include "create_epoll.h"
using namespace JSON_CS;

create_epoll::create_epoll(int sock) : s(sock), EPoll(epoll_create1(0)), Event(set_Event()), obj(add_obj()), obj_JSON(set_obj_JSON())
{
    er_epoll_create();

    // Регистрируем (добавляем дескр в epoll)
    er_epoll_ctl(this->s);

    set_epoll_wait();
}

create_epoll::~create_epoll()
{
    if (obj_JSON) cJSON_Delete(obj_JSON);
    if (query) cJSON_Delete(query);
}

std::map <std::string, int> create_epoll::add_obj()
{
    std::map <std::string, int> o;
    o["visa"] = 2;
    o["mir"] = 122;
    o["maestro"] = 57;
    o["mastercard"] = 184;
    return o;
}

cJSON* create_epoll::set_obj_JSON()
{
    if (obj_JSON) cJSON_Delete(obj_JSON);
    cJSON* oj = cJSON_CreateObject();
    for(auto& i : obj)
    {
        cJSON_AddNumberToObject(oj, i.first.c_str(), i.second);
    }
    pLog->Write("CHANGE SEQUENCE : %s\n", cJSON_Print(oj));

    return oj;
}

epoll_event create_epoll::set_Event()
{
    struct epoll_event Ev;
    Event.data.fd = s;
    Event.events = EPOLLIN | EPOLLET; // отслеживаем события при доступности на чтение
    return Ev;
}

void create_epoll::set_epoll_wait()
{
    while(N)
    {
        // Ожидаем событие
        N = epoll_wait(EPoll, Events, MAX_EVENTS, 5000 ); // последний аргумент -1
                                                           //- вечное ожидание,
                                                           //тогда while(1)
        er_epoll_wait();

        // пробегаемся по тем событиям, которые гарантированно отработали
        for( int i = 0; i < N; i++ )
        {
            if ((Events[i].events & EPOLLERR) ||
                    (Events[i].events & EPOLLHUP) ||
                    (!(Events[i].events & EPOLLIN)))
            {
                pLog->Write("Error in epoll\t | (Server) | \t%s",ctime(&lt));
                Close(Events[i].data.fd);
                throw(Bad_C_S_exception("Error in epoll\n"));
            }
            else if( Events[i].data.fd == s )
            {
                while(1)
                    if (Accept()==-1)
                        break;
                continue;
            }
            else
            {
                Answer(i);
            }
        Close(Events[i].data.fd);
        }
        if (N==0) return;
    }
}

int create_epoll::Accept()
{
    struct sockaddr in_addr;
    socklen_t in_len = sizeof in_addr;

    new_s = accept(s, &in_addr, &in_len);

    if(er_accept() == -1)
        return -1;

    get_info(in_addr, in_len);

    if ( Set_NonBlock(new_s) < 0 )
    {
        abort();
    }

    Event.data.fd = new_s;
    Event.events = EPOLLIN | EPOLLET;
    er_epoll_ctl(this->new_s);
    return 0;
}

void create_epoll::Answer(int i)
{
    Recv(i);
    std::string action = cJSON_GetObjectItem(query, "action")->valuestring;
    std::string sequence = cJSON_GetObjectItem(query, "sequence")->valuestring;;
    if (obj.find(sequence) == obj.end())
    {
        obj.insert(std::pair<std::string,int>(sequence,0));
        set_obj_JSON();
    }
    if ( action == "get" )
    {
        obj[sequence]++;
    }
    else if( action == "set" )
    {
        obj[sequence] = cJSON_GetObjectItem(query, "value")->valueint;
    }
    Send(i, sequence, obj[sequence]);
    obj_JSON = set_obj_JSON(); //обновление json
    //cJSON_Delete(query);
}

void create_epoll::Recv(int i)
{
    char Buffer[10000];
    memset(Buffer, 0, 10000);
    int RecvResult = recv(Events[i].data.fd, Buffer, 10000, 0);
    if ( RecvResult < 0 )
    {
        pLog->Write("Error Recv\t | (Server) | \t%s", ctime(&lt));
        Close(Events[i].data.fd);
        throw(Bad_C_S_exception("Error Recv\t | (Server) | \t%s"));
    }
    query = cJSON_Parse(Buffer);
}

void create_epoll::Send(int i, std::string sequence, int value)
{
    cJSON* answ = cJSON_CreateObject();
    cJSON_AddNumberToObject(answ, sequence.c_str(), value);
    std::string answer = cJSON_Print(answ);
    int SendResult = send(Events[i].data.fd, answer.c_str(), answer.size(), 0);
    if ( SendResult <= 0 )
    {
        pLog->Write("Error Send\t | (Server) | \t%s", ctime(&lt));
        throw(Bad_C_S_exception("Error Send"));
    }
    else
    {
        //printf("\n\nAnsw for Client %d :\n%s\n", count_client, answer.c_str());
        //pLog->Write("\nAnsw for Client %d :\n%s\n", count_client++, answer.c_str());
    }
    cJSON_Delete(answ);
}

int create_epoll::Set_NonBlock(int sfd)
{
    /*int flags;

    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1)
    {
        throw(Bad_C_S_exception("Error in SetNonBlock - fcntl - 1"));
        return -1;
    }

    flags |= O_NONBLOCK;
    if (fcntl (sfd, F_SETFL, flags) == -1)
    {
        throw(Bad_C_S_exception("Error in SetNonBlock - fcntl - 2"));
        return -1;
    }
    return 0;
    */
    int flags;
#ifdef O_NONBLOCK
    if ( (flags = fcntl(sfd, F_GETFL, 0)) == -1 ) {
        flags = 0;
        throw(Bad_C_S_exception("Error in SetNonBlock - fcntl - 1"));
    }
    return fcntl(sfd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return ioctl(sfd, FIOBIO, &flags);
#endif
}

void create_epoll::Close(int fd)
{
    //shutdown(fd, SHUT_RDWR);
    close(fd);
}

void create_epoll::get_info(struct sockaddr in_addr, socklen_t in_len)
{
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    int x = getnameinfo (&in_addr, in_len,
                         hbuf, sizeof hbuf,
                         sbuf, sizeof sbuf,
                         NI_NUMERICHOST | NI_NUMERICSERV);
    if ( x == 0 )
    {
        pLog->Write("Accepted connection on descriptor %d (host=%s, port=%s)\n", new_s, hbuf, sbuf);
        //printf("Accepted connection on descriptor %d (host=%s, port=%s)\n", new_s, hbuf, sbuf);
    }
}


void create_epoll::er_epoll_create()
{
    if( EPoll < 0 )
    {
        pLog->Write("Error in epol_create\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error in epoll_create"));
    }
    //pLog->Write("Epol_create\t | (Server) | \t%s",ctime(&lt));

}

void create_epoll::er_epoll_ctl(int sock)
{
    if ( epoll_ctl(EPoll, EPOLL_CTL_ADD, sock, &Event) < 0 )
    {
        pLog->Write("Error in epol_ctl\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error in epoll_ctl"));
    }
    //pLog->Write("Epol_ctl\t | (Server) | \t%s",ctime(&lt));
}

void create_epoll::er_epoll_wait()
{
    if( N < 0 )
    {
        pLog->Write("Error in epol_wait\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error in epoll_wait"));
    }
    //pLog->Write("Epol_wait\t | (Server) | \t%s",ctime(&lt));
}

int create_epoll::er_accept(){
    if( new_s < 0 )
    {
        if ((errno == EAGAIN) ||(errno == EWOULDBLOCK))
        {
            //pLog->Write("processed all incoming connections.\t | (Server) | \t%s",ctime(&lt));
            //printf ("processed all incoming connections.\n");
            return -1;
        }
        else if((errno == EMFILE))
        {
            perror("EMFILE ");
            pLog->Write("Error calling Accept\t | (Server) | \t%s", ctime(&lt));
            throw(Bad_C_S_exception("Error calling accept"));
            return -1;
        }
        else
        {
            pLog->Write("Error calling Accept\t | (Server) | \t%s", ctime(&lt));
            throw(Bad_C_S_exception("Error calling accept"));
            return -1;
        }
    }
    return 0;
    //pLog->Write("Accept\t\t | (Server) | \t%s",ctime(&lt));
}
