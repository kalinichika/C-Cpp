#include "jsonclient.h"
//#undef PRINT_LOG
using namespace JSON_CS;

client::client(const int port) noexcept(false)
    : net_resource(port)
{
    Connect();
}

client::~client() noexcept
{
#ifdef PRINT_LOG
    pLog->Write("Disonnect\t | (Client) | \t%s",ctime(&lt));
#endif
    close(s);
}

void client::Connect() const noexcept(false)
{
    if( connect( s, ( struct sockaddr * )&sock_addr, sizeof(sock_addr) ) < 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Error calling connect\t | (Client) | \t%s",ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error calling connect"));
    }
#ifdef PRINT_LOG
    pLog->Write("Connect\t\t | (Client) | \t%s",ctime(&lt));
#endif
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
#ifdef PRINT_LOG
        pLog->Write("Error Send query\t | (Client) | \t%s", ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error Send query"));
    }
    else
    {
        //printf("\nQuery for Server :\n%s\n", str.c_str());
#ifdef PRINT_LOG
        //pLog->Write("\nQuery for Server :\n%s\n", str.c_str());
#endif
    }
/*
    const int l = str.size();
    char length[5];
    sprintf(length,"%d",l);
    int res = send( s, length, 4, 0 );
    if ( res <= 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Error Send length\t | (Client) | \t%s", ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error Send length"));
    }
    //sleep(10);
    res = send( s, str.c_str(), l, 0 );
    if ( res <= 0 )
    {
#ifdef PRINT_LOG
        pLog->Write("Error Send query\t | (Client) | \t%s", ctime(&lt));
#endif
        throw(Bad_C_S_exception("Error Send query"));
    }
    else
    {
        printf("\nQuery for Server :\n%s\n", str.c_str());
#ifdef PRINT_LOG
        pLog->Write("\nQuery for Server :\n%s\n", str.c_str());
#endif
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
#ifdef PRINT_LOG
        pLog->Write("Error Recv\t | (Client) | ", stime(&lt));
#endif
        throw(Bad_C_S_exception("Error Recv"));
    }
    else
    {
        printf("Client %s:\n%s\n", cJSON_GetObjectItem(obj, "action")->valuestring, Buffer);
#ifdef PRINT_LOG
        pLog->Write("Client %s:\n%s\n", cJSON_GetObjectItem(obj, "action")->valuestring, Buffer);
#endif
    }
/*
    char length[5] = {0};
    int res =  recv(s, length, 4, 0);
    const int l = atoi(length);
    if (res<0)
    {
#ifdef PRINT_LOG
        pLog->Write("Error Recv\t | (Client) | ", stime(&lt));
#endif
        throw(Bad_C_S_exception("Error Recv length"));
    }

    char* Buffer = new char[l+1];
    memset(Buffer, 0, l);

    res =  recv(s, Buffer, l, 0);
    if (res<0)
    {
#ifdef PRINT_LOG
        pLog->Write("Error Recv\t | (Client) | ", stime(&lt));
#endif
        throw(Bad_C_S_exception("Error Recv length"));
    }
    else
    {
#ifdef PRINT_LOG
        pLog->Write("Client %s:\n%s\n", cJSON_GetObjectItem(obj, "action")->valuestring, Buffer);
#endif
    }
*/
}
