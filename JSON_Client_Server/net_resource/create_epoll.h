#ifndef CREATE_EPOLL_H
#define CREATE_EPOLL_H

#include "headers.h"
#include <map>
#define MAX_EVENTS 10000
namespace JSON_CS{

class create_epoll {
public:
    create_epoll(int);
    ~create_epoll();
private:
    int s, new_s;
    int EPoll;
    int N=1;
    struct epoll_event Event;
    struct epoll_event Events[MAX_EVENTS];
    unsigned int count_client = 0;
    Log *pLog = new Log(LogFileName);
    time_t lt = time(NULL);
private:
    std::map <std::string, int> obj;
    cJSON* obj_JSON = nullptr;
    cJSON* query;
private:
    cJSON* set_obj_JSON();
    std::map <std::string, int> add_obj();
private:
    epoll_event set_Event();
    void set_epoll_wait();
    int Accept();
    void Answer(int);
    void Recv(int);
    void Send(int, std::string, int);
    void get_info(struct sockaddr in_addr, socklen_t in_len);
    void Close(int);
    int Set_NonBlock(int);

    void er_epoll_create();
    void er_epoll_ctl(int sock);
    void er_epoll_wait();
    int er_accept();
};

}

#endif // CREATE_EPOLL_H

