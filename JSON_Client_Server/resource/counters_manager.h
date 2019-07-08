#ifndef COUNTERS_MANAGER_H
#define COUNTERS_MANAGER_H

#include "headers.h"
#include "counters.h"
#include "counters_view_json.h"
#define PRINT_LOG
#define MAX_EVENTS 10000
namespace JSON_CS{

class counters_manager {
public:
    counters_manager(int, const int);
    ~counters_manager();
private:
    int s;
    int EPoll;
    struct epoll_event Event;
    struct epoll_event Events[MAX_EVENTS];
    Log *pLog = new Log(LogFileName);
    time_t lt = time(NULL);
    counters obj;
private:
    epoll_event set_Event();
    void set_epoll_wait(const int time_for_wait);
    int  Accept();
    void Answer(int);
    cJSON* Recv(int);
    void Send(int, std::string, int);
    int  Set_NonBlock(int);
    void get_info(int, struct sockaddr in_addr, socklen_t in_len);
    int _epoll_create();
    int _epoll_ctl(int sock);
    int  er_epoll_wait(int);
    int  er_accept(int);
};

}

#endif // COUNTERS_MANAGER_H
