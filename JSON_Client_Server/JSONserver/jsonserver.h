#ifndef JSONSERVER_H
#define JSONSERVER_H

#include "/home/student/Projects/JSON_CS/net_resource/net_resource.h"
#include "/home/student/Projects/JSON_CS/net_resource/create_epoll.h"

namespace JSON_CS
{

class server : public net_resource
{
public:
    server(const unsigned int port = DEFAULT_PORT, const int time_for_wait = -1) noexcept(false);
    ~server() noexcept;
    void SConnect(const int time_for_wait);
private:
    void Bind() const;
    void Listen() const;
    void f_EPOLL(const int time_for_wait);
    void Answer(int i);
    void Recv(int i);
    void Send(int i);

    server(const server &other) = delete;
    server(server &&other) = delete;
    server operator = (const server &other) = delete;
    server operator = (server &&other) = delete;
};

}

#endif // JSONSERVER_H
