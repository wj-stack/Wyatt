//
// Created by Administrator on 2021/12/20.
//

#ifndef WYATT_LOGEVENTWRAP_H
#define WYATT_LOGEVENTWRAP_H

#include "LogEvent.h"
#include "Logger.h"
#include <memory>
//inline void WYATT_LOG_LEVEL(wyatt::Logger logger,wyatt::LogEvent event);



namespace wyatt{
    class LogEventWrap {
    public:
        LogEventWrap(Logger::ptr logger, LogEvent::ptr e);
        ~LogEventWrap();

    private:
        LogEvent::ptr m_event;
        Logger::ptr m_logger;
    };

}


#define WYATT_LOG_DEBUG(logger,s) \
    std::shared_ptr<wyatt::LogEventWrap>(new wyatt::LogEventWrap(logger,wyatt::LogEvent::ptr(new wyatt::LogEvent (wyatt::LogLevel::DEBUG , __FILE__, __LINE__, 0, 1, \
        2, time(0), s))));        \




//inline void WYATT_LOG_DEBUG2(wyatt::Logger::ptr logger,std::string s){
//
//    wyatt::LogEvent::ptr event (new wyatt::LogEvent (wyatt::LogLevel::DEBUG , __FILE__, __LINE__, 0, 1,
//                                                     2, time(0), s));
//
//std::make_shared<wyatt::LogEventWrap>(wyatt::LogEventWrap(logger,wyatt::LogEvent::ptr(new wyatt::LogEvent (wyatt::LogLevel::DEBUG , __FILE__, __LINE__, 0, 1,
//                                                                                      2, time(0), s))));
//
//}


#endif //WYATT_LOGEVENTWRAP_H
