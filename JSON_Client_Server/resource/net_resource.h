#ifndef NET_RESOURCE_H
#define NET_RESOURCE_H

#include "headers.h"

#define DEFAULT_PORT 12345

namespace JSON_CS
{

class net_resource
{
public:
    net_resource(const net_resource &other) = delete;
    net_resource(net_resource &&other) = delete;
    net_resource operator = (const net_resource &other) = delete;
    net_resource operator = (net_resource &&other) = delete;
protected:
    int  s;
    struct sockaddr_in sock_addr;
    Log *pLog = new Log(LogFileName);
    time_t lt = time(NULL);
protected:
    net_resource(const unsigned int port) : s(createSocket()), sock_addr(SockAddr(port)){}
    ~net_resource() { delete pLog; }

    int createSocket() noexcept(false);
    sockaddr_in SockAddr(const unsigned int port);
    int Set_NonBlock(int);
};


}

#endif // NET_RESOURCE_H
