#ifndef JSONSERVER_H
#define JSONSERVER_H
#define PRINT_LOG
#include "/home/student/Projects/JSON_CS/resource/net_resource.h"
#include "/home/student/Projects/JSON_CS/resource/counters_manager.h"
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
    void Communication(const int time_for_wait);
    server(const server &other) = delete;
    server(server &&other) = delete;
    server operator = (const server &other) = delete;
    server operator = (server &&other) = delete;
};
}

#endif // JSONSERVER_H
