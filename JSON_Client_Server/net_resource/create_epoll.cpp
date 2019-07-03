#include "create_epoll.h"
using namespace JSON_CS;

create_epoll::create_epoll(int sock) : s(sock), EPoll(epoll_create1(0)), Event(set_Event())
{
    er_epoll_create();

    // Регистрируем (добавляем дескр в epoll)
    er_epoll_ctl(this->s);
    set_epoll_wait();
}

create_epoll::~create_epoll(){}

epoll_event create_epoll::set_Event()
{
    struct epoll_event Ev;
    Event.data.fd = s;
    Event.events = EPOLLIN | EPOLLET; // отслеживаем события при доступности на чтение
    return Ev;
}

void create_epoll::set_epoll_wait()
{
    while(1)
    {
        // Ожидаем событие
        N = epoll_wait(EPoll, Events, MAX_EVENTS, -1); // -1 - вечное ожидание
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
                Work(i);
            }
        }
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

void create_epoll::Work(int i)
{
    char Buffer[1024];
    memset(Buffer, 0, 1024);
    int RecvResult = recv(Events[i].data.fd, Buffer, 1024, 0);
    if ( RecvResult < 0 )
    {
        pLog->Write("Error Recv\t | (Server) | \t%s", ctime(&lt));
        Close(Events[i].data.fd);
    }
    else if( RecvResult >0 )
    {
        //printf("Recv : \"%s\" | ( from Client %d) | \t%s", Buffer, count_client++, ctime(&lt));
        pLog->Write("Recv : \"%s\" | ( from Client %d) | \t%s", Buffer, count_client++, ctime(&lt));

        send(Events[i].data.fd, Buffer, RecvResult, 0);
    }
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
        else
        {
            pLog->Write("Error calling Accept\t | (Server) | \t%s",ctime(&lt));
            throw(Bad_C_S_exception("Error calling accept"));
            return -1;
        }
    }
    return 0;
    //pLog->Write("Accept\t\t | (Server) | \t%s",ctime(&lt));
}
