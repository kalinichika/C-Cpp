#include "counters.h"
using namespace JSON_CS;

counters::counters()
{
    m["visa"] = 0;
    m["mir"] = 0;
    m["maestro"] = 0;
    m["mastercard"] = 0;
}

counters::~counters()
{

}

int counters::Set(std::string str, int value)
{
    m[str] = value;
    return m[str];
}

int counters::Get(std::string str)
{
    if (m.count(str)) ( m[str] )++;
    else m[str] = 1;
    return m[str];
}
