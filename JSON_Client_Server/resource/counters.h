#ifndef COUNTERS_H
#define COUNTERS_H
#include <iostream>
#include <unordered_map>
namespace JSON_CS
{
class counters{
public:
    counters();
    ~counters();
    int Set(std::string, int);
    int Get(std::string);
    inline std::unordered_map<std::string, int> data() {return m;}
private:
    std::unordered_map<std::string, int> m;
};
}
#endif //COUNTERS_H
