#include "counters_view_json.h"
#define PRINT_LOG
using namespace JSON_CS;


counters_view_json::counters_view_json(counters obj)
{
    obj_JSON = cJSON_CreateObject();
    Update(obj);
}

counters_view_json::~counters_view_json()
{
    cJSON_Delete(obj_JSON);
    obj_JSON = nullptr;
    delete pLog;
}

void counters_view_json::Update(counters obj)
{
    if (obj_JSON) cJSON_Delete(obj_JSON);
    obj_JSON = nullptr;
    obj_JSON = cJSON_CreateObject();
    for(auto& i : obj.data())
    {
        cJSON_AddNumberToObject(obj_JSON, i.first.c_str(), i.second);
    }
}

void counters_view_json::Print(){
#ifdef PRINT_LOG
    pLog->Write("COUNTERS:%s", cJSON_Print(obj_JSON));
#endif
}

