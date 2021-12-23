//
// Created by Administrator on 2021/12/20.
//


#include "Logger.h"


wyatt::Logger::Logger(std::string name):m_name(std::move(name)){

}

void wyatt::Logger::addAppender(LogAppender::ptr appender) {
    m_appenders.push_back(appender);
}

void wyatt::Logger::delAppender(LogAppender::ptr appender) {
    for (auto it = m_appenders.begin(); it != m_appenders.end() ; it++) {
        if(*it == appender)
        {
            m_appenders.erase(it);
            break;
        }
    }
}

wyatt::LogLevel::Level wyatt::Logger::getLevel() const {
    return this->m_level;
}

void wyatt::Logger::setLevel(LogLevel::Level mLevel) {
    this->m_level = mLevel;
}

void wyatt::Logger::log(LogLevel::Level level, LogEvent::ptr event) {
    for(auto &appender:m_appenders)
    {
        appender->log(level,event);
    }
}

