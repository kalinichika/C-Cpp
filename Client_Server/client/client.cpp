#include "client.h"
using namespace Client_Server;

client::client(int port)
{
    // СОЗДАНИЕ СОКЕТА
    Socket();

    // СОЕДИНЕНИЕ ПО ОПРЕДЕЛЕННОМУ ПОРТУ С ХОСТОМ
    SockAddr(port);

    // должно отработать до accepta в сервере

    //ПОДКЛЮЧЕНИЕ К СЕРВЕРУ
    Connect();
}

client::~client()
{
    //РАЗРЫВ СОЕДИНЕНИЯ И ЗАКРЫТИЕ СОКЕТА
    Close();
}

void client::Connect()
{
    if( connect( s, ( struct sockaddr * )&sock_addr, sizeof(sock_addr) ) )
    {
        throw(Bad_C_S_exception("Error calling connect"));
    }
}

int client::findErrRecv(int result)
{
    if( result < 0 )
    {
        throw(Bad_C_S_exception("Error calling recv"));
        return 1;
    }
    if( result == 0 )
    {
        throw(Bad_C_S_exception("Server disconnected"));
        return 1;
    }
    return 0;
}

void client::Recv() noexcept
{
        int result;
        char length[2];
        unsigned short l = 0;

        //отработает после send в сервере

        result = recv (s, length, 2, 0 );
        if (findErrRecv(result)) return;
        memcpy(&l, (void*)length, 2);

        char* Buf = new char[l];
        memset(Buf, 0, l);

        result = recv( s, Buf, l, 0 );
        if (findErrRecv(result)) return;

        std::cout << "Message: " << Buf << std::endl;

        delete[] Buf;
}



