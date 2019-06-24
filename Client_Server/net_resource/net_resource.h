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
        int s;
        struct sockaddr_in sock_addr;

        net_resource() = default;
        virtual ~net_resource() = default;

        int Socket() noexcept(false);
        void SockAddr(int port = 12345);
        void Close();
    };

    class Bad_C_S_exception : public std::exception {
        const std::string error;

    public:
        Bad_C_S_exception(const std::string);

        Bad_C_S_exception(Bad_C_S_exception&& other);
        Bad_C_S_exception(const Bad_C_S_exception& other) = delete;
        Bad_C_S_exception operator = (Bad_C_S_exception&& other) = delete;
        Bad_C_S_exception operator = (const Bad_C_S_exception& other) = delete;
        ~Bad_C_S_exception() = default;\

        inline const std::string what() { return error; }
    };

}

#endif // NET_RESOURCE_H

