#ifndef JSONCLIENT_H
#define JSONCLIENT_H

#include "/home/student/Projects/JSON_CS/net_resource/net_resource.h"
#include "/home/student/Projects/JSON_CS/net_resource/log.h"

namespace JSON_CS
{

    class client : public net_resource
    {
    public:
        client (int num, int port = 12345) noexcept(false);
        ~client() noexcept;
        void Send() const noexcept;
        void Recv() const noexcept;
        void Connect() const;
    private:
        Log *pLog = new Log(LogFileName);
        time_t lt = time(NULL);
        unsigned int num;

        client(const client &other) = delete;
        client(client &other) = delete;
        client operator = (const client &other) = delete;
        client operator = (client &&other) = delete;
    };

}

#endif // JSONCLIENT_H
