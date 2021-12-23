//
// Created by Administrator on 2021/12/14.
//

#include "LogEvent.h"

#include <utility>

wyatt::LogLevel::Level wyatt::LogEvent::getLevel() const {
    return m_level;
}

const std::string &wyatt::LogEvent::getFileName() const {
    return fileName;
}

uint32_t wyatt::LogEvent::getLine() const {
    return line;
}

uint32_t wyatt::LogEvent::getThreadId() const {
    return threadId;
}

uint32_t wyatt::LogEvent::getFiberId() const {
    return fiberId;
}

uint64_t wyatt::LogEvent::getElapse() const {
    return elapse;
}

time_t wyatt::LogEvent::getTime() const {
    return time;
}

const std::string &wyatt::LogEvent::getContent() const {
    return content;
}

wyatt::LogEvent::LogEvent(LogLevel::Level mLevel, std::string fileName, uint32_t line, uint32_t threadId,
                   uint32_t fiberId, uint64_t elapse, time_t time, std::string content) : m_level(mLevel),
                                                                                          fileName(std::move(fileName)),
                                                                                          line(line),
                                                                                          threadId(threadId),
                                                                                          fiberId(fiberId),
                                                                                          elapse(elapse),
                                                                                          time(time),
                                                                                          content(std::move(content)) {
}

