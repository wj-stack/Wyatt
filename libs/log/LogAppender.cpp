//
// Created by Administrator on 2021/12/14.
//

#include "LogAppender.h"

void wyatt::LogAppender::setLevel(LogLevel::Level mLevel) {
    m_level = mLevel;
}

void wyatt::LogAppender::setFormatter(LogFormatter::ptr &mFormatter) {
    m_formatter = mFormatter;
}

wyatt::LogAppender::LogAppender(LogLevel::Level level) :m_level(level){

}


wyatt::StdoutLogAppender::StdoutLogAppender(LogLevel::Level level) : LogAppender(level) {

}

void wyatt::StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr ev) {
    if (level < m_level)
    {
        return;
    }
    std::cout << m_formatter->format(ev);
    std::cout.flush();
}
