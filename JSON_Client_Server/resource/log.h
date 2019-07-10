#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <stdarg.h>
#include <string>
#include <time.h>

#include "/home/student/Projects/JSON_CS/resource/bad_c_s_exception.h"
#define LogFileName "/home/student/Projects/JSON_CS/log.txt"


namespace JSON_CS
{
/* Класс для логирования*/
    class Log
    {
    public:
        Log(const std::string FileName = LogFileName);
        ~Log();
        void Write(const char* LogLine, ...);
    private:
        std::ofstream m_stream;
    };

}

#endif // LOG_H
