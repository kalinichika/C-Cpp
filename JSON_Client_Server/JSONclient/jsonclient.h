#ifndef JSONCLIENT_H
#define JSONCLIENT_H

#include "/home/student/Projects/JSON_CS/net_resource/net_resource.h"

namespace JSON_CS
{

    class client : public net_resource
    {
    public:
        client () noexcept(false);
        ~client() noexcept;
        void Send() const noexcept;
        void Recv() const noexcept;
    private:
        void Connect() const;

        unsigned int num = 0;

        client(const client &other) = delete;
        client(client &other) = delete;
        client operator = (const client &other) = delete;
        client operator = (client &&other) = delete;
    };

}

#endif // JSONCLIENT_H
