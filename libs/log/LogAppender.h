//
// Created by Administrator on 2021/12/14.
//

#ifndef WYATT_LOGAPPENDER_H
#define WYATT_LOGAPPENDER_H


#include <memory>
#include "LogLevel.h"
#include "LogFormatter.h"
#include <iostream>

namespace wyatt{
    class LogAppender {

    public:
        using ptr = std::shared_ptr<LogAppender>;

        explicit LogAppender(LogLevel::Level level);

        virtual ~LogAppender() = default;;

        void setLevel(LogLevel::Level mLevel);

        void setFormatter(LogFormatter::ptr &mFormatter);

        virtual void log(LogLevel::Level level, LogEvent::ptr ev) = 0;

    private:

    protected:
        LogLevel::Level m_level;
    // 默认格式化
    LogFormatter::ptr m_formatter = LogFormatter::ptr(new LogFormatter("[%d] [%p] [T:%t F:%F]%T%m%n"));

    };

    class StdoutLogAppender : public LogAppender {
    public:
        typedef std::shared_ptr<StdoutLogAppender> ptr;

        // thread-safe
        void log(LogLevel::Level level, LogEvent::ptr ev) override;

        explicit StdoutLogAppender(LogLevel::Level level = LogLevel::DEBUG);
    };


};

#endif //WYATT_LOGAPPENDER_H
