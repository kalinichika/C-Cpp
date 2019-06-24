#include "server.h"

int main()
{
    try {
        // СОЗДАНИЕ СЕРВЕРА С ПАРАМЕТРОМ (port)
        // по умолчанию port = 12345
        Client_Server::server Server(5555);

        // ОТПРАВКА ДАННЫХ
        char message[] = "Hello my friend!";
        Server.Send(sizeof(message), message);

        char message2[] = "My name is Viktoriya.";
        Server.Send(sizeof(message2), message2);
    }
    catch(Client_Server::Bad_C_S_exception &error){
        std::cout << error.what() << std::endl;
    }
    return 0;
}
