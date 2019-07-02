#include "jsonclient.h"
#include <vector>
#define max_client 1000
int main()
{
    try{
        // СОЗДАНИЕ КЛИЕНТА С ПАРАМЕТРАМИ (num, port)
        // num - номер клиента  по умолчанию 0
        // по умолчанию port = 12345

        std::vector <JSON_CS::client> Client(max_client);
        for(unsigned int i = 0; i < max_client; i++)
        {
            Client[i].Send();
            Client[i].Recv();
            printf ("it is Client %d\n\n", i);

        }

    }
    catch(JSON_CS::Bad_C_S_exception &error){
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
