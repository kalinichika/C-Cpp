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
    counters_manager(const int, const int);
    ~counters_manager();
    counters_manager(const counters_manager &other) = delete;
    counters_manager(counters_manager &&other) = delete;
    counters_manager operator = (const counters_manager &other) = delete;
    counters_manager operator = (counters_manager &&other) = delete;
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
    int  Recv1(const int i, const int size, int* length = nullptr);
    cJSON* Recv_query(const int i, const int length);
    void Send(const int, const std::string, const int);
    int  Accept();
    int  Set_NonBlock(const int);
    void get_info(const int, const struct sockaddr in_addr, const socklen_t in_len);
    int _epoll_create();
    int _epoll_ctl(const int sock);
    int  er_epoll_wait(const int);
    int  er_accept(const int);
};

}

#endif // COUNTERS_MANAGER_H
