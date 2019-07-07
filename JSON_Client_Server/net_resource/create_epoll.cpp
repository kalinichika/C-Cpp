#include "create_epoll.h"
using namespace JSON_CS;

create_epoll::create_epoll(int sock, const int time_for_wait) : s(sock)
{
    // Регистрируем (добавляем дескр в epoll)
    _epoll_ctl(s);

    set_epoll_wait(time_for_wait);
}

create_epoll::~create_epoll()
{
    close(EPoll);
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
    epLog->Write("CHANGE SEQUENCE : %s\n", cJSON_Print(oj));

    return oj;
}

epoll_event create_epoll::set_Event()
{
    struct epoll_event Ev;
    Ev.data.fd = s;
    Ev.events = EPOLLIN | EPOLLET | EPOLLPRI; // отслеживаем события при доступности на чтение
    return Ev;
}

void create_epoll::set_epoll_wait(const int time_for_wait)
{
    int N = 1;
    //int flag = 1;
    while(1)
    {
        // Ожидаем событие
        N = epoll_wait(EPoll, Events, MAX_EVENTS, time_for_wait );
        // последний аргумент -1 - вечное ожидание, тогда while(1)
        er_epoll_wait(N);

        // пробегаемся по тем событиям, которые гарантированно отработали
        for( int i = 0; i < N; i++ )
        {
            if ((Events[i].events & EPOLLERR) ||
                    (Events[i].events & EPOLLHUP) ||
                    (!(Events[i].events & EPOLLIN)))
            {
                epLog->Write("Error in epoll\t | (Server) | \t%s",ctime(&lt));
                close(Events[i].data.fd);
                throw(Bad_C_S_exception("Error in epoll\n"));
            }
            else if( Events[i].data.fd == s )
            {
                while(Accept()!=-1)

                    {
                        break;
                    }
                continue;
            }
            else if(Events[i].events & EPOLLIN)
            {
                std::cout<<"answer---";
                Answer(i);

            }
        }
        //if (N==0) return;
        //if (time_for_wait==-1) flag = 1;
        //else flag = N;
    }
}

int create_epoll::Accept()
{
    struct sockaddr in_addr;
    socklen_t in_len = sizeof in_addr;

    int new_s = accept(s, &in_addr, &in_len);

    if(er_accept(new_s) == -1)
        return -1;

    get_info(in_addr, in_len);

    Set_NonBlock(new_s);

    Event.data.fd = new_s;
    Event.events = EPOLLIN | EPOLLET;
    _epoll_ctl(new_s);
    return 0;
}

void create_epoll::Answer(int i)
{
    Recv(i);
    if (!query)
    {
        close(Events[i].data.fd);
        return;
    }
    std::string action = cJSON_GetObjectItem(query, "action")->valuestring;
    std::string sequence = cJSON_GetObjectItem(query, "sequence")->valuestring;;
    if ( obj.find(sequence) == obj.end() )
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
}

void create_epoll::Recv(int i)
{
    char Buffer[10000];
    memset(Buffer, 0, 10000);
    int res = recv(Events[i].data.fd, Buffer, 10000, 0);
    if ( res<0 )
    {
        epLog->Write("Error Recv\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error Recv"));
    }
    else if ( res == 0 )
    {
        close(Events[i].data.fd);
    }
    /*
    char length[5];
    int res = recv(Events[i].data.fd, length, 4, 0 );
    const int l = atoi(length);
    if (l == 0)
    {
        query = 0;
        return;
    }
    std::cout << l << " " << length << "\n";
    if ( res < 0 )
    {
        close(Events[i].data.fd);
        epLog->Write("Error Recv length\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error Recv length"));
    }

    char* Buffer = new char[l+1];
    memset(Buffer, 0, l+1);

    res = recv(Events[i].data.fd, Buffer, l, 0);
    if (res == 0)
    {
        close(Events[i].data.fd);
    }
    else if ( res<0 )
    {
        perror(" ");
        close(Events[i].data.fd);
        epLog->Write("Error Recv\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error Recv"));
    }
*/
    query = cJSON_Parse(Buffer);
}

void create_epoll::Send(int i, std::string sequence, int value)
{
    cJSON* answ = cJSON_CreateObject();
    cJSON_AddNumberToObject(answ, sequence.c_str(), value);
    const std::string answer (cJSON_Print(answ));

    int res = send( Events[i].data.fd, answer.c_str(), answer.size(), 0 );
    if ( res <= 0 )
    {
        epLog->Write("Error Send\t | (Server) | \t%s", ctime(&lt));
        throw(Bad_C_S_exception("Error Send"));
    }
    /*
    const int l = answer.size();
    char length[5] = {0};
    sprintf(length,"%d",l);
    std::cout<<l<<" "<<length<<"\n";
    int res = send( Events[i].data.fd, length, 4, 0 );
    if ( res <= 0 )
    {
        epLog->Write("Error Send\t | (Server) | \t%s", ctime(&lt));
        throw(Bad_C_S_exception("Error Send"));
    }

    res = send( Events[i].data.fd, answer.c_str(), l, 0 );
    if ( res <= 0 )
    {
        epLog->Write("Error Send\t | (Server) | \t%s", ctime(&lt));
        throw(Bad_C_S_exception("Error Send 1"));
    }
*/
    cJSON_Delete(answ);
}

int create_epoll::Set_NonBlock(int sfd)
{
    int flags;
#ifdef O_NONBLOCK
    if ( (flags = fcntl(sfd, F_GETFL, 0)) == -1 ) {
        flags = 0;
        throw(Bad_C_S_exception("Error in SetNonBlock - fcntl"));
    }
    return fcntl(sfd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return ioctl(sfd, FIOBIO, &flags);
#endif
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
        //epLog->Write("Accepted connection on descriptor %d (host=%s, port=%s)\n", new_s, hbuf, sbuf);
        //printf("Accepted connection on descriptor %d (host=%s, port=%s)\n", new_s, hbuf, sbuf);
    }
}

int create_epoll::_epoll_create()
{
    int e = epoll_create1(0);
    if( EPoll < 0 )
    {
        epLog->Write("Error in epol_create\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error in epoll_create"));
        return -1;
    }
    return e;
}

int create_epoll::_epoll_ctl(int sock)
{
    int e = epoll_ctl(EPoll, EPOLL_CTL_ADD, sock, &Event);
    if ( e < 0 )
    {
        epLog->Write("Error in epol_ctl\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error in epoll_ctl"));
        return -1;
    }
    return 0;
}

int create_epoll::er_epoll_wait(int N)
{
    if( N < 0 )
    {
        epLog->Write("Error in epol_wait\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error in epoll_wait"));
        return -1;
    }
    return 0;
}

int create_epoll::er_accept(int new_s){
    if( new_s < 0 )
    {
        if ((errno == EAGAIN) ||(errno == EWOULDBLOCK))
        {
            //pLog->Write("processed all incoming connections.\t | (Server) | \t%s",ctime(&lt));
            //printf ("processed all incoming connections.\n");
            //return -1;
        }
        else if((errno == EMFILE))
        {
            perror("EMFILE ");
            epLog->Write("Error calling Accept\t | (Server) | \t%s", ctime(&lt));
            throw(Bad_C_S_exception("Error calling accept"));
            return -1;
        }
        else
        {
            epLog->Write("Error calling Accept\t | (Server) | \t%s", ctime(&lt));
            throw(Bad_C_S_exception("Error calling accept"));
            return -1;
        }
    }
    return 0;
    //pLog->Write("Accept\t\t | (Server) | \t%s",ctime(&lt));
}
