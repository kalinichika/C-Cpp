#ifndef CLIENT_H
#define CLIENT_H

#include "/home/student/Study/Client_Server/net_resource/net_resource.h"
#include "/home/student/Projects/Client_Server/net_resource/log.h"

namespace Client_Server{

    class client : public net_resource
    {
    public:
        client (int port = 12345) noexcept(false);
        ~client() noexcept;
        void Recv() const noexcept;
    private:
        void Connect() const;
        int findErrRecv(int) const;
        Log *pLog = new Log(LogFileName);
        time_t lt = time(NULL);

        client(const client &other) = delete;
        client(client &other) = delete;
        client operator = (const client &other) = delete;
        client operator = (client &&other) = delete;
    };

}
#endif // CLIENT_H
