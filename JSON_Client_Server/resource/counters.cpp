#include "counters.h"
using namespace JSON_CS;

counters::counters()
{
    m["visa"] = 0;
    m["mir"] = 0;
    m["maestro"] = 0;
    m["mastercard"] = 0;
}

int counters::Set(const std::string str, const int value) noexcept
{
    m[str] = value;
    return m[str];
}

int counters::Get(const std::string str) noexcept
{
    if (m.count(str)) ( m[str] )++;
    else m[str] = 1;
    return m[str];
}
