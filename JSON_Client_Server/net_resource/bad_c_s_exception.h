#ifndef BAD_C_S_EXCEPTION_H
#define BAD_C_S_EXCEPTION_H

#include "/home/student/Projects/JSON_CS/net_resource/headers.h"

namespace JSON_CS
{

class Bad_C_S_exception : public std::exception {
    const std::string error;
public:
    Bad_C_S_exception(const std::string e) : error(e){}
    Bad_C_S_exception(Bad_C_S_exception&& other) : error(other.what()){}
    inline const std::string what(){ return error; }
};

}

#endif // BAD_C_S_EXCEPTION_H
