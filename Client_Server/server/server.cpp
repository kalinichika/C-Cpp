#include "server.h"
using namespace Client_Server;

server::server(const int port) noexcept(false)
{
        // СОЗДАЕМ СОКЕТ
        Socket();

        // ОПРЕДЕЛЯЕМ ПРОСЛУШИВАЕМЫЙ ПОРТ И АДРЕС
        SockAddr(port);
        Bind();

        // ЗАПУСКАЕМ ПРОСЛУШИВАНИЕ ВХОДЯЩИХ ПОКЛЮЧЕНИЙ
        Listen();

        // ПОЛУЧАЕМ ВХОДЯЩИЕ ПОДКЛЮЧЕНИЯ
        Accept();
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
    if( listen(s, 1) )
    {
        pLog->Write("Error calling Listen\t | (Server) | \t%s",ctime(&lt));
        throw("Error calling listen");
    }
    pLog->Write("Listen\t\t | (Server) | \t%s",ctime(&lt));
}

void server::Accept()
{
    s1 = accept(s, NULL, NULL);
    if( s1 < 0 )
    {
        pLog->Write("Error calling Accept\t | (Server) | \t%s",ctime(&lt));
        throw("Error calling accept");
    }
    pLog->Write("Accept\t\t | (Server) | \t%s",ctime(&lt));
}

void server::Send(const unsigned short l, const char* message) const noexcept(false)
{
    unsigned char length[2] = {0};
    memcpy((void*)length, &l, 2);


    if( send( s1, length, 2, 0 ) < 0 )
    {
        pLog->Write("Error sending response\t | (Server) | \t%s",ctime(&lt));
        throw("Error sending response");
        return;
    }
    pLog->Write("Send length\t | (Server) | \t%s",ctime(&lt));
    printf("Send length\n");

    if( send( s1, message, l, 0 ) < 0 )
    {
        pLog->Write("Error sending response\t | (Server) | \t%s",ctime(&lt));
        throw("Error sending response");
        return;
    }
    pLog->Write("Send message\t | (Server) | \t%s",ctime(&lt));
    printf("Send message\n\n");
}
