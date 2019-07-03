#include "bad_c_s_exception.h"
using namespace JSON_CS;

Bad_C_S_exception::Bad_C_S_exception(const std::string e) : error(e){}

Bad_C_S_exception::Bad_C_S_exception(Bad_C_S_exception&& other) : error(other.what()){}
