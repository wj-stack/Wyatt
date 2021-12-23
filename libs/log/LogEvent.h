//
// Created by Administrator on 2021/12/14.
//

#ifndef WYATT_LOGEVENT_H
#define WYATT_LOGEVENT_H

#include <stdint.h>
#include <string>
#include <memory>
#include "LogLevel.h"

namespace wyatt{
    class LogEvent {
    public:
        typedef std::shared_ptr<LogEvent> ptr;

        LogLevel::Level getLevel() const;

        const std::string &getFileName() const;

        uint32_t getLine() const;

        uint32_t getThreadId() const;

        uint32_t getFiberId() const;

        uint64_t getElapse() const;

        time_t getTime() const;

        const std::string &getContent() const;

        LogEvent(LogLevel::Level mLevel, std::string fileName, uint32_t line, uint32_t threadId, uint32_t fiberId,
                 uint64_t elapse, time_t time, std::string content);

    private:
        LogLevel::Level m_level;  //日志等级
        std::string fileName; // 文件名
        uint32_t line = 0;  // 行号
        uint32_t threadId; // 线程id
        uint32_t fiberId; // 协程id
        uint64_t elapse;  // 运行毫秒数
        time_t  time;// 时间戳
        std::string content; // 文本内容

    };



}
#endif //WYATT_LOGEVENT_H
