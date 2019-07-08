#ifndef JSONCLIENT_H
#define JSONCLIENT_H

#include "/home/student/Projects/JSON_CS/resource/net_resource.h"

namespace JSON_CS
{

class client : public net_resource
{
public:
    client (int port = DEFAULT_PORT) noexcept(false);
    ~client() noexcept;
    void Connect() const noexcept(false);
    void Disconnect() noexcept;
    void Set(std::string, int) const noexcept(false);
    void Get(std::string) const noexcept(false);
private:
    void Send(std::string) const noexcept(false);
    void Recv(cJSON*) const noexcept(false);
    client(const client &other) = delete;
    client(client &other) = delete;
    client operator = (const client &other) = delete;
    client operator = (client &&other) = delete;
};

}

#endif // JSONCLIENT_H
