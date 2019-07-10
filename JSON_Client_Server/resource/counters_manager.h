#ifndef COUNTERS_MANAGER_H
#define COUNTERS_MANAGER_H

#include "headers.h"
#include "counters.h"
#include "counters_view_json.h"
#define PRINT_LOG
#undef PRINT_CONS
#define MAX_EVENTS 10000
namespace JSON_CS{
/* Класс  * для обеспечения параллельной работы с клиентами
 *              с использованием технологий epoll
 *        * для работы со счетчиками
 *              с использованием классов counters, counters_view_json
 * (Обьект данного класса создается в сервере)
 *
 * Функциональность:
 * Создание контекста опроса событий        ( используется epoll_create1(0) )
 * Добавление фд в заданный контекст опроса ( используется epoll_ctl(..) )
 * Ожидание событий на фд                   ( используется epoll_wait(..) )
 * Установление связи с клиентами           ( используется accept(..) )
 * Общение с клиентом ( формат JSON )       ( используется recv(..) и send (..)
 *
 * Предусмотрена корректная работа и защита от зависания
 *          при побайтовой отправки запросов клиентами.
 *  */
class counters_manager {
public:
    counters_manager(const int, const int);
    ~counters_manager();
    counters_manager(const counters_manager &other) = delete;
    counters_manager(counters_manager &&other) = delete;
    counters_manager operator = (const counters_manager &other) = delete;
    counters_manager operator = (counters_manager &&other) = delete;
private:
    // Создание контекста опроса событий
    int _epoll_create();
    epoll_event set_Event();

    // Добавление дескрипторов в заданный контекст опроса
    int _epoll_ctl(const int sock);

    // Ожидание событий на фд
    void set_epoll_wait(const int time_for_wait);
    int  er_epoll_wait(const int);

    // Установление связи с клиентами
    int  Accept();
    int  er_accept(const int);
    int  Set_NonBlock(const int);
    void get_info(const int, const struct sockaddr in_addr, const socklen_t in_len);

    // Функции для общения с клиентом
    int  Recv1(const int i, const int size, int* length = nullptr);
    cJSON* Recv_query(const int i, const int length);
    void Send(const int, const std::string, const int);

private:
    int s;
    int EPoll;
    struct epoll_event Event;
    struct epoll_event Events[MAX_EVENTS];
    Log *pLog = new Log(LogFileName);
    time_t lt = time(NULL);
    counters obj;
};

}

#endif // COUNTERS_MANAGER_H
