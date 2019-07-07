#include "/home/student/Projects/JSON_CS/JSONclient/jsonclient.h"
using namespace JSON_CS;

client::client(const int port) noexcept(false)
    : net_resource(port)
{
    Connect();
}

client::~client() noexcept
{
    pLog->Write("Disonnect\t | (Client) | \t%s",ctime(&lt));
    close(s);
}

void client::Connect() const noexcept(false)
{
    if( connect( s, ( struct sockaddr * )&sock_addr, sizeof(sock_addr) ) < 0 )
    {
        pLog->Write("Error calling connect\t | (Client) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error calling connect"));
    }
    pLog->Write("Connect\t\t | (Client) | \t%s",ctime(&lt));
}

void client::Set(std::string sequence, int value) const noexcept(false)
{
    cJSON* obj = cJSON_CreateObject();
    cJSON_AddStringToObject(obj, "action", "set");
    cJSON_AddStringToObject(obj, "sequence", sequence.c_str());
    cJSON_AddNumberToObject(obj, "value", value);
    Send(cJSON_Print(obj));
    Recv(obj);
    cJSON_Delete(obj);
}

void client::Get(std::string sequence) const noexcept(false)
{
    cJSON* obj = cJSON_CreateObject();
    cJSON_AddStringToObject(obj, "action", "get");
    cJSON_AddStringToObject(obj,  "sequence", sequence.c_str());
    Send(cJSON_Print(obj));
    Recv(obj);
    cJSON_Delete(obj);
}

void client::Send( std::string str) const noexcept(false)
{
    //std::string str(cJSON_Print(obj));

    int res = send( s, str.c_str(), str.size(), 0 );
    if ( res <= 0 )
    {
        pLog->Write("Error Send query\t | (Client) | \t%s", ctime(&lt));
        throw(Bad_C_S_exception("Error Send query"));
    }
    else
    {
        //printf("\nQuery for Server :\n%s\n", str.c_str());
        //pLog->Write("\nQuery for Server :\n%s\n", str.c_str());
    }
/*
    const int l = str.size();
    char length[5];
    sprintf(length,"%d",l);
    //std::cout<<l<<" "<<length;
    int res = send( s, length, 4, 0 );
    if ( res <= 0 )
    {
        pLog->Write("Error Send length\t | (Client) | \t%s", ctime(&lt));
        throw(Bad_C_S_exception("Error Send length"));
    }

    res = send( s, str.c_str(), l, 0 );
    if ( res <= 0 )
    {
        pLog->Write("Error Send query\t | (Client) | \t%s", ctime(&lt));
        throw(Bad_C_S_exception("Error Send query"));
    }
    else
    {
        printf("\nQuery for Server :\n%s\n", str.c_str());
        pLog->Write("\nQuery for Server :\n%s\n", str.c_str());
    }
*/
}

void client::Recv(cJSON* obj) const noexcept(false)
{

    char Buffer[10000];
    memset(Buffer, 0, 10000);

    int res =  recv(s, Buffer, 10000, 0) ;

    if ( res < 0 )
    {
        pLog->Write("Error Recv\t | (Client) | ", stime(&lt));
        throw(Bad_C_S_exception("Error Recv"));
    }
    else
    {
        printf("Client %s:\n%s\n", cJSON_GetObjectItem(obj, "action")->valuestring, Buffer);
        pLog->Write("Client %s:\n%s\n", cJSON_GetObjectItem(obj, "action")->valuestring, Buffer);
    }
/*

    char length[5] = {0};
    int res =  recv(s, length, 4, 0);
    const int l = atoi(length);
    std::cout<<l<<" "<<length;
    if (res<0)
    {
        pLog->Write("Error Recv\t | (Client) | ", stime(&lt));
        throw(Bad_C_S_exception("Error Recv length"));
    }

    char* Buffer = new char[l+1];
    memset(Buffer, 0, l);

    res =  recv(s, Buffer, l, 0);
    if (res<0)
    {
        pLog->Write("Error Recv\t | (Client) | ", stime(&lt));
        throw(Bad_C_S_exception("Error Recv length"));
    }
    else
    {
        printf("Client %s:\n%s\n", cJSON_GetObjectItem(obj, "action")->valuestring, Buffer);
        pLog->Write("Client %s:\n%s\n", cJSON_GetObjectItem(obj, "action")->valuestring, Buffer);
    }
*/
}
