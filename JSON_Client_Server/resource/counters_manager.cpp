#include "/home/student/Projects/JSON_CS/resource/counters_manager.h"
#define PRINT_LOG
using namespace JSON_CS;

counters_manager::counters_manager(int sock, const int time_for_wait) : s(sock), EPoll(_epoll_create()), Event(set_Event())
{
    // Регистрируем (добавляем дескр в epoll)
    _epoll_ctl(s);

    set_epoll_wait(time_for_wait);
}

counters_manager::~counters_manager()
{
    close(EPoll);
    delete pLog;
}

epoll_event counters_manager::set_Event()
{
    struct epoll_event Ev;
    Ev.data.fd = s;
    Ev.events = EPOLLIN; // отслеживаем события при доступности на чтение
    return Ev;
}

void counters_manager::set_epoll_wait(const int time_for_wait)
{
    int N = 1;
    int _exit_while = 0;
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
#ifdef PRINT_LOG
                pLog->Write("Error in epoll\t | (Server) | \t%s",ctime(&lt));
#endif
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
                cJSON* query = nullptr;
                counters_view_json obj_json(obj);
                int length;
                int size = 4;
                while(!query && !_exit_while)
                {
                    switch ( Recv1(i, size, &length) )
                    {
                    case 1:
                        close(Events[i].data.fd);
                        _exit_while = 1;
                        continue;
                    case 2:
                    {
                        sleep(1);
                        continue;
                    }
                    case 3:
                    {
                        if ( length <= 0 )
                        {
                            close(Events[i].data.fd);
                            continue;
                        }
                        size = length + 4;
                        continue;
                    }
                    case 0:
                        query = Recv_query(i, length);
                        size = 4;
                        continue;
                    }
                }
                if(_exit_while)
                {
                    _exit_while = 0;
                    continue;
                }
                if (query)
                {
#ifdef PRINT_LOG
                    pLog->Write("Server Recv:%s",cJSON_Print(query));
#endif
                    std::string action = cJSON_GetObjectItem(query, "action")->valuestring;
                    std::string sequence = cJSON_GetObjectItem(query, "sequence")->valuestring;;
                    if ( action == "get" )  Send(i, sequence, obj.Get(sequence));
                    else if( action == "set" )  Send(i, sequence, obj.Set(sequence, cJSON_GetObjectItem(query, "value")->valueint));
                    obj_json.Update(obj);
                    obj_json.Print();
                    cJSON_Delete(query);
                    query = nullptr;
                }
                else
                {
                    close(Events[i].data.fd);
                    cJSON_Delete(query);
                    query = nullptr;
                    continue;
                }
            }
        }
        //if (N==0) return;
    }
}

int counters_manager::Accept()
{
    struct sockaddr in_addr;
    socklen_t in_len = sizeof in_addr;

    int new_s = accept(s, &in_addr, &in_len);

    if(er_accept(new_s) == -1)
        return -1;

    get_info(new_s, in_addr, in_len);

    Set_NonBlock(new_s);

    Event.data.fd = new_s;
    Event.events = EPOLLIN | EPOLLET;
    _epoll_ctl(new_s);
    return 0;
}

int counters_manager::Recv1(const int i, const int size, int *length)
{
    char Buffer[size];
    memset(Buffer, 0, size);
    int res = recv(Events[i].data.fd, Buffer, size, MSG_PEEK );
    if ( res <= 0 )
    {
        return 1;
    }
    else if ( (res<size)&&(res>0) )
    {
        return 2;
    }
    else if ( size == 4 )
    {
        *length = atoi(Buffer);
        return 3;
    }
    else if ( size > 4 )
    {
        return 0;
    }
    return res;
}

cJSON* counters_manager::Recv_query(const int i, const int length)
{
    cJSON* query = cJSON_CreateObject();
    char l[4];
    recv(Events[i].data.fd, l, 4, 0);

    char* Buffer = new char[length];
    memset(Buffer, 0, length);
    int res = recv(Events[i].data.fd, Buffer, length, 0);
    if ( res <= 0 ) close(Events[i].data.fd);
    else if ( res > 0 ) query = cJSON_Parse(Buffer);
    return query;
}

void counters_manager::Send(int i, std::string sequence, int value)
{
    cJSON* answ = cJSON_CreateObject();
    cJSON_AddNumberToObject(answ, sequence.c_str(), value);
    const std::string answer(cJSON_Print(answ));
    /*
    int res = send( Events[i].data.fd, answer.c_str(), answer.size(), 0 );
    if ( res <= 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Error Send\t | (Server) | \t%s", ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error Send Server"));
    }
#ifdef PRINT_LOG
    pLog->Write("Server Send:%s", answer.c_str());
#endif
*/
    const int l = answer.size();
    char length[5] = {0};
    sprintf(length,"%d",l);
    int res = send( Events[i].data.fd, length, 4, 0 );
    if ( res <= 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Error Send\t | (Server) | \t%s", ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error Send"));
    }
    //sleep(10);
    res = send( Events[i].data.fd, answer.c_str(), l, 0 );
    if ( res <= 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Error Send\t | (Server) | \t%s", ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error Send 1"));
    }
#ifdef PRINT_LOG
    pLog->Write("Server Send:%s", answer);
#endif

    cJSON_Delete(answ);
    answ = nullptr;
}

int counters_manager::Set_NonBlock(int sfd)
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

void counters_manager::get_info(int new_s, struct sockaddr in_addr, socklen_t in_len)
{
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    int x = getnameinfo (&in_addr, in_len,
                         hbuf, sizeof hbuf,
                         sbuf, sizeof sbuf,
                         NI_NUMERICHOST | NI_NUMERICSERV);
    if ( x == 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Accepted connection on descriptor %d (host=%s, port=%s)\n", new_s, hbuf, sbuf);
#endif
        //printf("Accepted connection on descriptor %d (host=%s, port=%s)\n", new_s, hbuf, sbuf);
    }
}

int counters_manager::_epoll_create()
{
    int e = epoll_create1(0);
    if( EPoll < 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Error in epol_create\t | (Server) | \t%s",ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error in epoll_create"));
        return -1;
    }
    return e;
}

int counters_manager::_epoll_ctl(int sock)
{
    int e = epoll_ctl(EPoll, EPOLL_CTL_ADD, sock, &Event);
    if ( e < 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Error in epol_ctl\t | (Server) | \t%s",ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error in epoll_ctl"));
        return -1;
    }
    return 0;
}

int counters_manager::er_epoll_wait(int N)
{
    if( N < 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Error in epol_wait\t | (Server) | \t%s",ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error in epoll_wait"));
        return -1;
    }
    return 0;
}

int counters_manager::er_accept(int new_s){
    if( new_s < 0 )
    {
        if ((errno == EAGAIN) ||(errno == EWOULDBLOCK))
        {
#ifdef PRINT_LOG
            //pLog->Write("processed all incoming connections.\t | (Server) | \t%s",ctime(&lt));
#endif
            //printf ("processed all incoming connections.\n");
            //return -1;
        }
        else if((errno == EMFILE))
        {
            perror("EMFILE ");
#ifdef PRINT_LOG
            pLog->Write("Error calling Accept\t | (Server) | \t%s", ctime(&lt));
#endif
            throw(Bad_C_S_exception("Error calling accept"));
            return -1;
        }
        else
        {
#ifdef PRINT_LOG
            pLog->Write("Error calling Accept\t | (Server) | \t%s", ctime(&lt));
#endif
            throw(Bad_C_S_exception("Error calling accept"));
            return -1;
        }
    }
    return 0;
#ifdef PRINT_LOG
    //pLog->Write("Accept\t\t | (Server) | \t%s",ctime(&lt));
#endif
}
