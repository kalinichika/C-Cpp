#include "log.h"

using namespace Client_Server;

Log::Log(const std::string FileName) {
    m_stream.open(FileName,std::ios::app);
}

void Log::Write(const char* LogLine, ...) {
    va_list argList;
    char cbuffer[1024];
    va_start(argList, LogLine);
    vsnprintf(cbuffer, 1024, LogLine, argList);
    va_end(argList);
    m_stream << cbuffer << std::endl;
}

Log::~Log() {
    m_stream.close();
}
