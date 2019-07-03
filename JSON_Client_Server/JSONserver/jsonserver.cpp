#include "jsonserver.h"
using namespace JSON_CS;

server::server() noexcept(false)

{
    SConnect();
}

server::~server() noexcept
{
    //РАЗРЫВ СОЕДИНЕНИЯ И ЗАКРЫТИЕ СОКЕТА
    pLog->Write("Disconnect\t | (Server) | \t%s",ctime(&lt));
    Close(s);
}

void server::SConnect()
{
    Bind();

    // Неблокирующий режим
    Set_NonBlock(this->s);

    // ЗАПУСКАЕМ ПРОСЛУШИВАНИЕ ВХОДЯЩИХ ПОКЛЮЧЕНИЙ
    Listen();

    // Все махинации с epoll
    f_EPOLL();
}

void server::Bind() const
{
    if( bind(s, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0 )
    {
        pLog->Write("Error calling bind\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error calling bind"));
    }
    pLog->Write("Bind\t\t | (Server) | \t%s",ctime(&lt));

}

void server::Listen() const
{
    if( listen(s, SOMAXCONN) ) // SOMAXCONN - максимальное кол соединений, поддерживаемых системой.
    {
        pLog->Write("Error calling Listen\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error calling listen"));
    }
    pLog->Write("Listen\t\t | (Server) | \t%s",ctime(&lt));
}

void server::f_EPOLL(){
    create_epoll myEpoll(this->s);
}


