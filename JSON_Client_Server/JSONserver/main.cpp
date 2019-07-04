#include "jsonserver.h"

int main()
{
    try
    {
        // по умолчанию port = 12345

        JSON_CS::server Server;

    }
    catch(JSON_CS::Bad_C_S_exception &error)
    {
        std::cout << error.what() << std::endl;
    }

    return 0;
}
