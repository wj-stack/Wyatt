//
// Created by Administrator on 2021/12/14.
//

#include "LogLevel.h"



std::string wyatt::LogLevel::levelToString(LogLevel::Level level)
{
    std::string result;
    switch (level)
    {
        case DEBUG:
            result = "DEBUG";
            break;
        case INFO:
            result = "INFO";
            break;
        case WARN:
            result = "WARN";
            break;
        case ERROR:
            result = "ERROR";
            break;
        case FATAL:
            result = "FATAL";
            break;
        case UNKNOWN:
            result = "UNKNOWN";
            break;
    }
    return result;
}

