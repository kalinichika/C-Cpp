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
    pLog->Write("Disconnect\t | (Server) | \t%s",ctime(&lt));
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
    f_EPOLL(time_for_wait);
}

void server::Bind() const
{
    //чтобы избежать проблем с "Address already in use"
    int opt = 1;
    if (setsockopt (s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt)) == -1) perror("setsockopt");

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

void server::f_EPOLL(const int time_for_wait){
    create_epoll myEpoll(this->s, time_for_wait);
    //_epoll_create();

    // Регистрируем (добавляем дескр в epoll)
    //_epoll_ctl(s);

    //set_epoll_wait(time_for_wait);
}
/*
void server::Answer(int i)
{
    Recv(i);
    if (!query)
    {
        close(Events[i].data.fd);
        return;
    }
    std::string action = cJSON_GetObjectItem(query, "action")->valuestring;
    std::string sequence = cJSON_GetObjectItem(query, "sequence")->valuestring;;
    if ( obj.find(sequence) == obj.end() )
    {
        obj.insert(std::pair<std::string,int>(sequence,0));
        set_obj_JSON();
    }
    if ( action == "get" )
    {
        obj[sequence]++;
    }
    else if( action == "set" )
    {
        obj[sequence] = cJSON_GetObjectItem(query, "value")->valueint;
    }
    Send(i, sequence, obj[sequence]);
    obj_JSON = set_obj_JSON(); //обновление json
}

void server::Recv(int i)
{
    char Buffer[10000];
    memset(Buffer, 0, 10000);
    int res = recv(Events[i].data.fd, Buffer, 10000, 0);
    if ( res<0 )
    {
        pLog->Write("Error Recv\t | (Server) | \t%s",ctime(&lt));
        throw(Bad_C_S_exception("Error Recv"));
    }
    else if ( res == 0 )
    {
        close(Events[i].data.fd);
    }
    query = cJSON_Parse(Buffer);
}

void server::Send(int i)
{
    cJSON* answ = cJSON_CreateObject();
    cJSON_AddNumberToObject(answ, sequence.c_str(), value);
    const std::string answer (cJSON_Print(answ));

    int res = send( Events[i].data.fd, answer.c_str(), answer.size(), 0 );
    if ( res <= 0 )
    {
        pLog->Write("Error Send\t | (Server) | \t%s", ctime(&lt));
        throw(Bad_C_S_exception("Error Send"));
    }
    cJSON_Delete(answ);
}
*/



