#include "/home/student/Projects/JSON_CS/JSONclient/jsonclient.h"
#include <vector>
const unsigned int max_client = 500;
int main()
{
    try{

        // по умолчанию port = 12345

        std::vector <JSON_CS::client>  Client1(max_client);
        for(unsigned int i = 0; i < max_client; i++)
        {
            Client1[i].Send();
            Client1[i].Recv();
            printf ("it is Client %d\n\n", i);
        }
        sleep(5);
    }
    catch(JSON_CS::Bad_C_S_exception &error){
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
