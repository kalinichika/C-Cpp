#include "net_resource.h"
using namespace JSON_CS;

int net_resource::Set_NonBlock(int sfd)
{
    /*int flags;

    flags = fcntl (sfd, F_GETFL, 0);
    if (flags == -1)
    {
        throw(Bad_C_S_exception("Error in SetNonBlock - fcntl - 1"));
        return -1;
    }

    flags |= O_NONBLOCK;
    if (fcntl (sfd, F_SETFL, flags) == -1)
    {
        throw(Bad_C_S_exception("Error in SetNonBlock - fcntl - 2"));
        return -1;
    }
    return 0;*/

    int flags;
    #ifdef O_NONBLOCK
        if ( (flags = fcntl(sfd, F_GETFL, 0)) == -1 ) {
            flags = 0;
        }
        return fcntl(sfd, F_SETFL, flags | O_NONBLOCK);
    #else
        flags = 1;
        return ioctl(sfd, FIOBIO, &flags);
    #endif
}

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
void net_resource::SockAddr()
{
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(12345);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void net_resource::Close()
{
    close(s);
}

Bad_C_S_exception::Bad_C_S_exception(const std::string e) : error(e){}

Bad_C_S_exception::Bad_C_S_exception(Bad_C_S_exception&& other) : error(other.what()){}
