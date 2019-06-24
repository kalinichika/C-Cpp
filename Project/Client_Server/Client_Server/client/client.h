#ifndef CLIENT_H
#define CLIENT_H

#include "/home/student/Projects/net_resource/net_resource.h"

namespace Client_Server{

class client : public net_resource
{
public:
    client(int port = 12345);
    ~client();

    void Recv();

private:
    void Connect();
    int findErrRecv(int);

};

}
#endif // CLIENT_H
