//
// Created by Administrator on 2021/12/20.
//

#ifndef WYATT_LOGGER_H
#define WYATT_LOGGER_H


#include <memory>
#include <string>
#include "Logger.h"
#include "LogAppender.h"
#include <utility>
#include <list>
#include "LogEvent.h"

namespace wyatt{

    // 日志器
    class Logger {
    public:
        using ptr = std::shared_ptr<Logger>;
        Logger(std::string name = "root");
        void log(LogLevel::Level level, LogEvent::ptr event);
        void addAppender(LogAppender::ptr appender);
        void delAppender(LogAppender::ptr appender);
        LogLevel::Level getLevel() const;
        void setLevel(LogLevel::Level mLevel);

    private:
        // 日志器名称
        std::string m_name;
        LogLevel::Level m_level; // 日志器级别
        std::list<LogAppender::ptr> m_appenders; // appender集合
    };

}

#endif //WYATT_LOGGER_H
