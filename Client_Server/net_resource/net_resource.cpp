#include "net_resource.h"
using namespace Client_Server;

// СОЗДАЕМ СОКЕТ
int net_resource::Socket()
{
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0)
    {
        throw(Bad_C_S_exception("Error calling socket"));
        return 0;
    }
    return s;
}

// ОПРЕДЕЛЯЕМ ПРОСЛУШИВАЕМЫЙ ПОРТ И АДРЕС
void net_resource::SockAddr(int port){
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

void net_resource::Close()
{
    close(s);
}

Bad_C_S_exception::Bad_C_S_exception(const std::string e) : error(e){}

Bad_C_S_exception::Bad_C_S_exception(Bad_C_S_exception&& other) : error(other.what()){}


