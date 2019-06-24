#include "client.h"
using namespace Client_Server;

client::client(int port) noexcept(false)
{
    // СОЗДАНИЕ СОКЕТА
    Socket();

    // СОЕДИНЕНИЕ ПО ОПРЕДЕЛЕННОМУ ПОРТУ С ХОСТОМ
    SockAddr(port);

    // должно отработать до accepta в сервере

    //ПОДКЛЮЧЕНИЕ К СЕРВЕРУ
    Connect();
}

client::~client() noexcept
{
    //РАЗРЫВ СОЕДИНЕНИЯ И ЗАКРЫТИЕ СОКЕТА
    pLog->Write("Disonnect\t | (Client) | \t%s",ctime(&lt));
    Close();
}

void client::Connect() const
{
    if( connect( s, ( struct sockaddr * )&sock_addr, sizeof(sock_addr) ) )
    {
        pLog->Write("Error calling connect\t | (Client) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error calling connect"));
    }
    pLog->Write("Connect\t\t | (Client) | \t%s",ctime(&lt));
}

int client::findErrRecv(int result) const
{
    if( result < 0 )
    {
        pLog->Write("Error calling recv\t | (Client) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error calling recv"));
        return 1;
    }
    if( result == 0 )
    {
        pLog->Write("Server disconnected\t | (Client) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Server disconnected"));
        return 1;
    }
    return 0;
}

void client::Recv() const noexcept
{
        int result;
        char length[2];
        unsigned short l = 0;

        //отработает после send в сервере

        result = recv (s, length, 2, 0 );
        if (findErrRecv(result)) return;
        pLog->Write("Receive length\t | (Client) | \t%s",ctime(&lt));
        memcpy(&l, (void*)length, 2);

        char* Buf = new char[l];
        memset(Buf, 0, l);

        result = recv( s, Buf, l, 0 );
        if (findErrRecv(result)) return;
        pLog->Write("Receive message\t | (Client) | \t%s",ctime(&lt));

        pLog->Write("MESSAGE: %s\n",Buf);
        std::cout << "Message: " << Buf << std::endl;

        delete[] Buf;
}



