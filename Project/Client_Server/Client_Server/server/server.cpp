#include "server.h"
using namespace Client_Server;

server::server(int port)
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

server::~server()
{
    Close();
    //printf("Close Server\n");
}

void server::Bind()
{
    if( bind(s, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0 )
    {
        throw("Error calling bind");
    }
}

void server::Listen()
{
    if( listen(s, 1) )
    {
        throw("Error calling listen");
    }
}

void server::Accept()
{
    s1 = accept(s, NULL, NULL);
    if( s1 < 0 )
    {
        throw("Error calling accept");
    }
}

void server::Send(unsigned short l, char* message)
{
    unsigned char length[2] = {0};
    memcpy((void*)length, &l, 2);


    if( send( s1, length, 2, 0 ) < 0 )
    {
        throw("Error sending response");
        return;
    }
    printf("Response send length\n");

    if( send( s1, message, l, 0 ) < 0 )
    {
        throw("Error sending response");
        return;
    }
    printf("Response send message\n\n");
}
