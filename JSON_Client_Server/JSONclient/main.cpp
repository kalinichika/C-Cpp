#include "/home/student/Projects/JSON_CS/JSONclient/jsonclient.h"
#include <vector>
int main()
{
    try{
        JSON_CS::client Client(12345);
        Client.Get("mir");
        Client.Get("visa");
        JSON_CS::client Client2(12345);
        Client2.Set("other", 100);
    }
    catch(JSON_CS::Bad_C_S_exception &error){
        perror("");
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
