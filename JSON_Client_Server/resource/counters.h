#ifndef COUNTERS_H
#define COUNTERS_H
#include <iostream>
#include <unordered_map>
namespace JSON_CS
{
/* Класс счетчиков (создается в counters_manager):
 * Set -  устанавливает значение счетчика в указанное значение
 * Get -  увеличивает значение счетчика на 1 с каждым запросом */
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
