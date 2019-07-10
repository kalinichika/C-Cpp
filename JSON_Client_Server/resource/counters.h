#ifndef COUNTERS_H
#define COUNTERS_H
#include <iostream>
#include <unordered_map>
namespace JSON_CS
{
class counters{
public:
    counters();
    ~counters() = default;
    int Set(const std::string, const int) noexcept;
    int Get(const std::string) noexcept;
    inline std::unordered_map<std::string, int> data() const noexcept {return m;}
private:
    std::unordered_map<std::string, int> m;
};
}
#endif //COUNTERS_H
