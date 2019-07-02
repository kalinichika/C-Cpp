#ifndef JSONSERVER_H
#define JSONSERVER_H

#include "/home/student/Projects/JSON_CS/net_resource/net_resource.h"
#include "/home/student/Projects/JSON_CS/net_resource/log.h"

namespace JSON_CS
{

    class server : public net_resource
    {
    public:
        server(unsigned int port = 12345) noexcept(false);
        ~server() noexcept;
    private:
        void Bind() const;
        void Listen() const;
        void f_EPOLL();
        void Accept();

        int new_s;

        Log *pLog = new Log(LogFileName);
        time_t lt = time(NULL);

        server(const server &other) = delete;
        server(server &&other) = delete;
        server operator = (const server &other) = delete;
        server operator = (server &&other) = delete;
    };

}

#endif // JSONSERVER_H
