#ifndef JSONCLIENT_H
#define JSONCLIENT_H
#undef PRINT_LOG
#include "/home/student/Projects/JSON_CS/resource/net_resource.h"

namespace JSON_CS
{

class client : public net_resource
{
public:
    client (const int port = DEFAULT_PORT) noexcept(false);
    ~client() noexcept;
    void Connect() const noexcept(false);
    void Set(const std::string, const int) const noexcept(false);
    void Get(const std::string) const noexcept(false);
private:
    void Send(const std::string) const noexcept(false);
    void Recv(const cJSON*) const noexcept(false);
    client(const client &other) = delete;
    client(client &other) = delete;
    client operator = (const client &other) = delete;
    client operator = (client &&other) = delete;
};

}

#endif // JSONCLIENT_H
