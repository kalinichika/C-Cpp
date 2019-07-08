#ifndef COUNTERS_VIEW_JSON_H
#define COUNTERS_VIEW_JSON_H
#include "cJSON.h"
#include "log.h"
#include "counters.h"
#include <unordered_map>
#define LogFileName "/home/student/Projects/JSON_CS/log.txt"
namespace JSON_CS
{
class counters_view_json{
public:
    counters_view_json(counters obj);
    ~counters_view_json();
    void Update(counters obj);
    void Print();
private:
    cJSON* obj_JSON;
    Log *pLog = new Log(LogFileName);
};
}
#endif // COUNTERS_VIEW_JSON_H
