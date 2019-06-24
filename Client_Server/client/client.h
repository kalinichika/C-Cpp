#ifndef CLIENT_H
#define CLIENT_H

#include "/home/student/Projects/Client_Server/net_resource/net_resource.h"

namespace Client_Server{

class client : public net_resource
{
public:
    client (int port = 12345);
    ~client();

    void Recv() noexcept;

private:
    void Connect();
    int findErrRecv(int);

};

}
#endif // CLIENT_H
