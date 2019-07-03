#ifndef JSONSERVER_H
#define JSONSERVER_H

#include "/home/student/Projects/JSON_CS/net_resource/net_resource.h"
#include "/home/student/Projects/JSON_CS/net_resource/create_epoll.h"

namespace JSON_CS
{

class server : public net_resource
{
public:
    server() noexcept(false);
    ~server() noexcept;

private:
    void SConnect();
    void Bind() const;
    void Listen() const;
    void f_EPOLL();

    server(const server &other) = delete;
    server(server &&other) = delete;
    server operator = (const server &other) = delete;
    server operator = (server &&other) = delete;
};

}

#endif // JSONSERVER_H
