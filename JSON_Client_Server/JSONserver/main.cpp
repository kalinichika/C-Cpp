#include "jsonserver.h"

int main()
{
    try
    {
        // СОЗДАНИЕ СЕРВЕРА С ПАРАМЕТРОМ (port)
        // по умолчанию port = 12345

        JSON_CS::server Server;
        //Server.Rec();

    }
    catch(JSON_CS::Bad_C_S_exception &error)
    {
        std::cout << error.what() << std::endl;
    }

    return 0;
}
