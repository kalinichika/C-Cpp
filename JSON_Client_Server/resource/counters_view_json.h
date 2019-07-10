#ifndef COUNTERS_VIEW_JSON_H
#define COUNTERS_VIEW_JSON_H
#include "cJSON.h"
#include "log.h"
#include "counters.h"
#define PRINT_LOG
#define LogFileName "/home/student/Projects/JSON_CS/log.txt"
namespace JSON_CS
{
/* Класс счетчиков в формате JSON:
 * Update -  вызывается после изменений в counters и соотвующим образом изменяет объект JSON
 * Print  -  вывод в файл лога счетчиков в формате JSON */
class counters_view_json{
public:
    counters_view_json(const counters obj);
    ~counters_view_json();
    void Update(counters obj) noexcept;
    void Print() const noexcept;
private:
    cJSON* obj_JSON;
    Log *pLog = new Log(LogFileName);
};
}
#endif // COUNTERS_VIEW_JSON_H
