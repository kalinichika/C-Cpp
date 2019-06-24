#ifndef SERVER_H
#define SERVER_H

#include "/home/student/Projects/Client_Server/net_resource/net_resource.h"
namespace Client_Server{

class server : public net_resource
{
public:
    server(int port = 12345);
    ~server();

    int s1;

    void Send(unsigned short, char*) noexcept(false);

private:
    void Bind();
    void Accept();
    void Listen();

};

}

#endif // SERVER_H
