#ifndef SERVER_H
#define SERVER_H

#include "/home/student/Study/Client_Server/net_resource/net_resource.h"
#include "/home/student/Projects/Client_Server/net_resource/log.h"

namespace Client_Server{

    class server : public net_resource
    {
    public:
        server(const int port = 12345) noexcept(false);
        ~server() noexcept;
        void Send(const unsigned short, const char*) const noexcept(false);
    private:
        void Bind() const;
        void Accept();
        void Listen() const;
        int s1;
        Log *pLog = new Log(LogFileName);
        time_t lt = time(NULL);

        server(const server &other) = delete;
        server(server &&other) = delete;
        server operator = (const server &other) = delete;
        server operator = (server &&other) = delete;
    };

}

#endif // SERVER_H
