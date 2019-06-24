#include "client.h"

int main()
{
    try{
        // СОЗДАНИЕ КЛИЕНТА С ПАРАМЕТРОМ (port)
        // по умолчанию port = 12345
        Client_Server::client Client(5555);

        // ПОЛУЧЕНИЕ ДАННЫХ
        Client.Recv();
    }
    catch(Client_Server::Bad_C_S_exception &error){
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
