#ifndef NET_RESOURCE_H
#define NET_RESOURCE_H

#include <iostream>
//#include <algorithm>
//#include <set>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <errno.h>

#include <stdarg.h>

#define MAX_EVENTS 1024

namespace JSON_CS
{

    class net_resource
    {
    private:
        net_resource(const net_resource &other) = delete;
        net_resource(net_resource &&other) = delete;
        net_resource operator = (const net_resource &other) = delete;
        net_resource operator = (net_resource &&other) = delete;
    protected:
        int  s;
        struct sockaddr_in sock_addr;

        net_resource() = default;
        virtual ~net_resource() = default;

        int Socket() noexcept(false);
        void SockAddr();
        void Close();
        int Set_NonBlock(int);
    };

    class Bad_C_S_exception : public std::exception {
        const std::string error;
    public:
        Bad_C_S_exception(const std::string);
        Bad_C_S_exception(Bad_C_S_exception&& other);
        inline const std::string what(){ return error; }
    };

}

#endif // NET_RESOURCE_H

