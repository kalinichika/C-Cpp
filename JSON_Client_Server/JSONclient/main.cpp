#include "/home/student/Projects/JSON_CS/JSONclient/jsonclient.h"
#include <vector>
const unsigned int max_client = 50;
int main()
{
    try{
        std::vector <JSON_CS::client>  Client(max_client);
        for(unsigned int i = 0; i < max_client-1; i++)
        {
            if (i%5 == 0)
            {
                printf ("%d ", i);
                Client[i].Get("mir");
            }
            else if (i%5 == 1)
            {
                printf ("%d ", i);
                Client[i].Get("visa");
            }
            else if (i%5 == 2)
            {
                printf ("%d ", i);
                Client[i].Get("maestro");
            }
            else if (i%5 == 3)
            {
                printf ("%d ", i);
                Client[i].Get("mastercard");
            }
            else if (i%5 == 4)
            {
                printf ("%d ", i);
                Client[i].Get("other");
            }
        }
        printf ("%d ", max_client-1);
        Client[max_client-1].Set("visa",1);
        //sleep(5);
    }
    catch(JSON_CS::Bad_C_S_exception &error){
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
