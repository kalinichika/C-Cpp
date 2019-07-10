#include "jsonserver.h"
using namespace JSON_CS;

server::server(const unsigned int port, const int time_for_wait) noexcept(false)
    :net_resource(port)
{
    SConnect(time_for_wait);
}

server::~server() noexcept
{
    //РАЗРЫВ СОЕДИНЕНИЯ И ЗАКРЫТИЕ СОКЕТА
#ifdef PRINT_LOG
    pLog->Write("Disconnect\t | (Server) | \t%s",ctime(&lt));
#endif
    close(s);
}

void server::SConnect(const int time_for_wait)
{
    Bind();

    // Неблокирующий режим
    Set_NonBlock(this->s);

    // ЗАПУСКАЕМ ПРОСЛУШИВАНИЕ ВХОДЯЩИХ ПОКЛЮЧЕНИЙ
    Listen();

    // Все махинации с epoll
    Communication(time_for_wait);
}

void server::Bind() const
{
    //чтобы избежать проблем с "Address already in use"
    int opt = 1;
    if (setsockopt (s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt)) == -1) perror("setsockopt");

    if( bind(s, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Error calling bind\t | (Server) | \t%s",ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error calling bind"));
    }
    pLog->Write("Bind\t\t | (Server) | \t%s",ctime(&lt));

}

void server::Listen() const
{
    if( listen(s, SOMAXCONN) ) // SOMAXCONN - максимальное кол-во соединений, поддерживаемых системой.
    {
#ifdef PRINT_LOG
        pLog->Write("Error calling Listen\t | (Server) | \t%s",ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error calling listen"));
    }
#ifdef PRINT_LOG
    pLog->Write("Listen\t\t | (Server) | \t%s",ctime(&lt));
#endif
}

void server::Communication(const int time_for_wait){
    counters_manager manager(this->s, time_for_wait);
}




