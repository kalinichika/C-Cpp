#include "/home/student/Projects/JSON_CS/JSONclient/jsonclient.h"
using namespace JSON_CS;

client::client() noexcept(false)
{
    // должно отработать до accepta в сервере
    Connect();
}

client::~client() noexcept
{
    //РАЗРЫВ СОЕДИНЕНИЯ И ЗАКРЫТИЕ СОКЕТА
    //pLog->Write("Disonnect\t | (Client) | \t%s",ctime(&lt));
    Close(s);
}

void client::Connect() const
{
    if( connect( s, ( struct sockaddr * )&sock_addr, sizeof(sock_addr) ) < 0 )
    {
        pLog->Write("Error calling connect\t | (Client) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error calling connect"));
    }
    //pLog->Write("Connect\t\t | (Client) | \t%s",ctime(&lt));
}

void client::Send() const noexcept
{
    std::string  Buffer(ctime(&lt));
    send(s, &Buffer[0], sizeof(Buffer), 0);
    //pLog->Write("Send message\t | (Client) | \t%s", ctime(&lt));
    //printf("Send message\t | (Client) | \t%s", ctime(&lt));
}

void client::Recv() const noexcept
{
    char Buffer[1024];
    memset(Buffer, 0, 1024);
    int RecvResult = recv(s, Buffer, 1024, 0);
    if ( RecvResult < 0 )
    {
        pLog->Write("Error Recv\t | (Client) | \t%s", ctime(&lt));
    }
    else {
        printf("Recv : %s", Buffer);
        //pLog->Write("Recv : \"%s\" | (Client) | \t%s", Buffer, ctime(&lt));
    }
}


