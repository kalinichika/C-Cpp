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

    int s1;

    void Send(const unsigned short, const char*) const noexcept(false);

private:
    void Bind() const;
    void Accept();
    void Listen() const;

    Log *pLog = new Log("/home/student/Study/Client_Server/log.txt");
    time_t lt = time(NULL);
};

}

#endif // SERVER_H
