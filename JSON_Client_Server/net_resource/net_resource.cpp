#include "net_resource.h"
using namespace JSON_CS;

// СОЗДАЕМ СОКЕТ
int net_resource::createSocket()
{
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0)
    {
        if(errno==EMFILE) perror("EMFILE");
        throw(Bad_C_S_exception("Error calling socket"));
        return 0;
    }
    return s;
}

// ОПРЕДЕЛЯЕМ ПРОСЛУШИВАЕМЫЙ ПОРТ И АДРЕС
sockaddr_in net_resource::SockAddr()
{
    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(DEFAULT_PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    return sa;
}

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
            throw(Bad_C_S_exception("Error in SetNonBlock - fcntl - 1"));
        }
        return fcntl(sfd, F_SETFL, flags | O_NONBLOCK);
    #else
        flags = 1;
        return ioctl(sfd, FIOBIO, &flags);
    #endif
}


void net_resource::Close(int fd)
{
    //shutdown(fd, SHUT_RDWR);
    close(fd);
}
