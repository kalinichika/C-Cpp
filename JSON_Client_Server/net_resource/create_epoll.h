#ifndef CREATE_EPOLL_H
#define CREATE_EPOLL_H

#include "headers.h"
#include <map>
#define MAX_EVENTS 10000
namespace JSON_CS{

class create_epoll {
public:
    create_epoll(int, const int);
    ~create_epoll();
private:
    int s;
    //int new_s;
    int EPoll = _epoll_create();
    struct epoll_event Event = set_Event();
    struct epoll_event Events[MAX_EVENTS];
    //unsigned int count_client = 0;

    Log *epLog = new Log(LogFileName);
    time_t lt = time(NULL);
private:
    std::map <std::string, int> obj = add_obj();
    cJSON* obj_JSON = nullptr;
    cJSON* query;
    cJSON* set_obj_JSON();
    std::map <std::string, int> add_obj();
private:
    epoll_event set_Event();
    void set_epoll_wait(const int time_for_wait);
    int  Accept();
    void Answer(int);
    void Recv(int);
    void Send(int, std::string, int);
    void get_info(struct sockaddr in_addr, socklen_t in_len);
    int Set_NonBlock(int);     //

    int _epoll_create();      //+
    int _epoll_ctl(int sock); //+
    int  er_epoll_wait(int);      //
    int  er_accept(int);          //
};

}

#endif // CREATE_EPOLL_H

