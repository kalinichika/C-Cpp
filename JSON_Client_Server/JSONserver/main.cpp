#include "jsonserver.h"
#include <cstdio>
int main()
{

    remove(LogFileName);
    try
    {
        // по умолчанию port = 12345
        // параметр - time for epoll_wait (-1 - вечное ожидание)
        JSON_CS::server Server(12345, -1);

    }
    catch(JSON_CS::Bad_C_S_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
    return 0;
}


