#include "/home/student/Projects/JSON_CS/JSONclient/jsonclient.h"
#include <vector>
#include <unordered_map>
int main()
{
    std::unordered_map <int,int> m;
    m.count(1);
    try{
        JSON_CS::client Client(12345);
        Client.Get("visa");
        //Client.Set("mir",1);
        //Client.Set("lol",7);
        //Client.Get("other");
    }
    catch(JSON_CS::Bad_C_S_exception &error)
    {
        std::cout<<error.what()<<std::endl;
    }
    return 0;
}
