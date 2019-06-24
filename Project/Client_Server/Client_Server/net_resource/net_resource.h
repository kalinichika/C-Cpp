#ifndef NET_RESOURCE_H
#define NET_RESOURCE_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

namespace Client_Server{

    class net_resource{
    protected:
        net_resource();
        virtual ~net_resource();

        int s;
        struct sockaddr_in sock_addr;

        int Socket();
        void SockAddr(int port = 12345);
        void Close();
    };

    class Bad_C_S_exception : public std::exception {
        const std::string error;
    public:
        Bad_C_S_exception(const std::string);
        const std::string what();
    };

}

#endif // NET_RESOURCE_H

