#include "jsonclient.h"

int main()
{
    try{
        // СОЗДАНИЕ КЛИЕНТА С ПАРАМЕТРАМИ (num, port)
        // num - номер клиента
        // по умолчанию port = 12345
        unsigned int max_cl = 1000;
        for(unsigned int i = 0; i < max_cl; i++)
        {
            JSON_CS::client Client(i, 5555);
            Client.Connect();
            Client.Send();
            Client.Recv();
        }

    }
    catch(JSON_CS::Bad_C_S_exception &error){
        std::cout<<error.what()<<std::endl;
    }
}
