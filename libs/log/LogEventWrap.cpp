
#include "LogEventWrap.h"

#include <utility>
#include <thread>


wyatt::LogEventWrap::LogEventWrap(Logger::ptr logger, LogEvent::ptr e): m_logger(logger) ,m_event(e) {
//    std::cout << "begin" << std::endl;
}

wyatt::LogEventWrap::~LogEventWrap() {
    if(m_logger && m_event)
    {
        m_logger->log(m_event->getLevel(),m_event);
    }
//    std::cout << "end" << std::endl;
}
