#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <stdarg.h>
#include <string>
#include <time.h>

namespace Client_Server{

    class Log {
    public:
        Log(const std::string FileName);
        ~Log() noexcept;
        void Write(const char* LogLine, ...) noexcept;
    private:
        std::ofstream m_stream;
    };

}

#endif // LOG_H
