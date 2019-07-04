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
    pLog->Write("Disonnect\t | (Client) | \t%s",ctime(&lt));
    Close(s);
    cJSON_Delete(obj);
}

void client::Connect() const
{
    if( connect( s, ( struct sockaddr * )&sock_addr, sizeof(sock_addr) ) < 0 )
    {
        pLog->Write("Error calling connect\t | (Client) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error calling connect"));
    }
    pLog->Write("Connect\t\t | (Client) | \t%s",ctime(&lt));
}

void client::Set(std::string sequence, int value)
{
    cJSON_AddStringToObject(obj, "action", "set");
    cJSON_AddStringToObject(obj, "sequence", sequence.c_str());
    cJSON_AddNumberToObject(obj, "value", value);

    Send();
    Recv();
}

void client::Get(std::string sequence)
{
    cJSON_AddStringToObject(obj, "action", "get");
    cJSON_AddStringToObject(obj,  "sequence", sequence.c_str());

    Send();
    Recv();
}

void client::Send() const noexcept
{
    std::string str = cJSON_Print(obj);
    int SendResult = send(s, str.c_str(), str.size(), 0);

    if ( SendResult <= 0 )
    {
        pLog->Write("Error Send\t | (Client) | \t%s", ctime(&lt));
        throw(Bad_C_S_exception("Error Send"));
    }
    else
    {
        printf("\nQuery for Server :\n%s\n", str.c_str());
        pLog->Write("\nQuery for Server :\n%s\n", str.c_str());
    }
}

void client::Recv() const noexcept
{
    char Buffer[1000];
    memset(Buffer, 0, 1000);
    int RecvResult = recv(s, Buffer, 1000, 0);
    if ( RecvResult < 0 )
    {
        pLog->Write("Error Recv\t | (Client) | \t%s", ctime(&lt));
        throw(Bad_C_S_exception("Error Recv"));
    }
    else {
        //char* answ = cJSON_Print(cJSON_Parse(Buffer));
        printf("Client %s:\n%s\n",cJSON_GetObjectItem(obj, "action")->valuestring, Buffer);
        pLog->Write("Client %s: \n%s\n",cJSON_GetObjectItem(obj, "action")->valuestring, Buffer);
    }
}



