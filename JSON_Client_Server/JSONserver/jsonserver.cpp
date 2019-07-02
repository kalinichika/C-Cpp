#include "jsonserver.h"
using namespace JSON_CS;

server::server(const int port) noexcept(false)
{
        // СОЗДАЕМ СОКЕТ
        Socket();

        // ОПРЕДЕЛЯЕМ ПРОСЛУШИВАЕМЫЙ ПОРТ И АДРЕС
        SockAddr(port);
        Bind();

        // Неблокирующий режим
        Set_NonBlock(this->s);

        // ЗАПУСКАЕМ ПРОСЛУШИВАНИЕ ВХОДЯЩИХ ПОКЛЮЧЕНИЙ
        Listen();

        // Все махинации с epoll
        f_EPOLL();

}

server::~server() noexcept
{
    //РАЗРЫВ СОЕДИНЕНИЯ И ЗАКРЫТИЕ СОКЕТА
    pLog->Write("Disconnect\t | (Server) | \t%s",ctime(&lt));
    Close();
}

void server::Bind() const
{
    if( bind(s, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0 )
    {
        pLog->Write("Error calling bind\t | (Server) | \t%s",ctime(&lt));
        throw("Error calling bind");
    }
    pLog->Write("Bind\t\t | (Server) | \t%s",ctime(&lt));

}

void server::Listen() const
{
    if( listen(s, 5) )
    {
        pLog->Write("Error calling Listen\t | (Server) | \t%s",ctime(&lt));
        throw("Error calling listen");
    }
    pLog->Write("Listen\t\t | (Server) | \t%s",ctime(&lt));
}

void server::Accept()
{


}



void server::f_EPOLL()
{
    // Задаем дескриптор epoll
    int EPoll;
    if( (EPoll = epoll_create1(0)) < 0 )
    {
        pLog->Write("Error in epol_create\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error in epoll_create"));
    }
    pLog->Write("Epol_create\t | (Server) | \t%s",ctime(&lt));

    // Зарегистрируем s в epoll
    struct epoll_event Event;
    Event.data.fd = s;
    Event.events = EPOLLIN | EPOLLET; // отслеживаем события при доступности на чтение
                            // | EPOLLET;

    // Регистрируем (добавляем дескр в epoll)
    if ( epoll_ctl(EPoll, EPOLL_CTL_ADD, s, &Event) < 0 )
    {
        pLog->Write("Error in epol_ctl\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error in epoll_ctl"));
    }
    pLog->Write("Epol_ctl\t | (Server) | \t%s",ctime(&lt));


    while(1){
        struct epoll_event Events[MAX_EVENTS];
        // Ожидаем событие
        int N = epoll_wait(EPoll, Events, MAX_EVENTS, -1); // -1 - вечное ожидание
        if( N < 0 )
        {
            pLog->Write("Error in epol_wait\t | (Server) | \t%s",ctime(&lt));
            throw(Bad_C_S_exception("Error in epoll_wait"));
        }
        pLog->Write("Epol_wait\t | (Server) | \t%s",ctime(&lt));

        // пробегаемся по тем событиям, которые гарантированно отработали
        for( int i = 0; i < N; i++ )
        {
            pLog->Write("i = %d\t\t | (Server) | \t%s",i,ctime(&lt));

            if ((Events[i].events & EPOLLERR) ||
                    (Events[i].events & EPOLLHUP) ||
                    (!(Events[i].events & EPOLLIN)))
            {
                pLog->Write("Error in epoll\t | (Server) | \t%s",ctime(&lt));
                close (Events[i].data.fd);
                throw(Bad_C_S_exception("Error in epoll\n"));
            }

            else if( Events[i].data.fd == s )
            {
                while(1)
                {



                    struct sockaddr in_addr;
                    socklen_t in_len;
                    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
                    in_len = sizeof in_addr;

                    new_s = accept(s, &in_addr, &in_len);



                    if( new_s < 0 )
                    {
                        if ((errno == EAGAIN) ||(errno == EWOULDBLOCK))
                        {
                            pLog->Write("processed all incoming connections.\t | (Server) | \t%s",ctime(&lt));
                            printf ("processed all incoming connections.\n");
                            break;
                        }
                        else
                        {
                            pLog->Write("Error calling Accept\t | (Server) | \t%s",ctime(&lt));
                            throw("Error calling accept");
                            break;

                        }
                    }
                    pLog->Write("Accept\t\t | (Server) | \t%s",ctime(&lt));

                    int x = getnameinfo (&in_addr, in_len,
                                 hbuf, sizeof hbuf,
                                 sbuf, sizeof sbuf,
                                 NI_NUMERICHOST | NI_NUMERICSERV);
                    if ( x == 0 )
                    {
                        printf("Accepted connection on descriptor %d (host=%s, port=%s)\n", new_s, hbuf, sbuf);
                    }

                    // делаем его неблокирующим
                    //if( new_s > 0)
                    //{
                        if ( Set_NonBlock(this->new_s) < 0 )
                        {
                            printf("\nABORT\n");
                            abort();
                        }
                    //}




                    Event.data.fd = new_s;
                    Event.events = EPOLLIN | EPOLLET;
                    if ( epoll_ctl(EPoll, EPOLL_CTL_ADD, new_s, &Event) < 0 )
                    {
                        pLog->Write("Error in epol_ctl after Accept()\t | (Server) | \t%s",ctime(&lt));
                        throw(Bad_C_S_exception("Error in epoll_ctl after Accept()"));
                    }
                }
                continue;
            }
            else
            {
                pLog->Write("Buffer\t\t | (Server) | \t%s",ctime(&lt));
                char Buffer[1024];
                memset(Buffer, 0, 1024);
                int RecvResult = recv(Events[i].data.fd, Buffer, 1024, 0);
                if ( RecvResult < 0 )
                {
                    pLog->Write("Error Recv\t | (Server) | \t%s", ctime(&lt));
                    shutdown(Events[i].data.fd, SHUT_RDWR);
                    close(Events[i].data.fd);                  //// Close()
                }
                else if( RecvResult >0 )
                {
                    printf("Recv : \"%s\" | (Server) | \t%s", Buffer, ctime(&lt));
                    pLog->Write("Recv : \"%s\" | (Server) | \t%s", Buffer, ctime(&lt));

                    send(Events[i].data.fd, Buffer, RecvResult, 0);
                }
            }
        }
    }
}


