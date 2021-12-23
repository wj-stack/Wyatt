//
// Created by Administrator on 2021/12/14.
//

#ifndef WYATT_FORMATITEM_H
#define WYATT_FORMATITEM_H


#include <memory>
#include <utility>
#include <ctime>
#include "LogEvent.h"
#include <ostream>

namespace wyatt{

    class FormatItem {
    public:
        typedef std::shared_ptr<FormatItem> ptr;

        virtual void format(std::ostream &out, LogEvent::ptr ev) = 0;
    };

    class PlainFormatItem : public FormatItem {
    public:
        explicit PlainFormatItem(std::string str) : m_str(std::move(str)) {}

        void format(std::ostream &out, LogEvent::ptr ev) override {
            out << m_str;
        }

    private:
        std::string m_str;
    };

    class LevelFormatItem : public FormatItem {
    public:
        void format(std::ostream &out, LogEvent::ptr ev) override {
            out << LogLevel::levelToString(ev->getLevel());
        }
    };

    class FilenameFormatItem : public FormatItem {
    public:
        void format(std::ostream &out, LogEvent::ptr ev) override {
            out << ev->getFileName();
        }
    };

    class LineFormatItem : public FormatItem {
    public:
        void format(std::ostream &out, LogEvent::ptr ev) override {
            out << ev->getLine();
        }
    };

    class ThreadIDFormatItem : public FormatItem {
    public:
        void format(std::ostream &out, LogEvent::ptr ev) override {
            out << ev->getThreadId();
        }
    };

    class FiberIDFormatItem : public FormatItem {
    public:
        void format(std::ostream &out, LogEvent::ptr ev) override {
            out << ev->getFiberId();
        }
    };

    class TimeFormatItem : public FormatItem {
    public:
        explicit TimeFormatItem(std::string str = "%Y-%m-%d %H:%M:%S")
        : m_time_pattern(std::move(str)) {
            if (m_time_pattern.empty()) {
                m_time_pattern = "%Y-%m-%d %H:%M:%S";
            }
        }

        void format(std::ostream &out, LogEvent::ptr ev) override {
            struct tm time_struct
                    {
                    };
            time_t time_l = ev->getTime();
            localtime_r(&time_l, &time_struct);
            char buffer[64]{0};
            strftime(buffer, sizeof(buffer),
                     m_time_pattern.c_str(), &time_struct);
            out << buffer;
        }

    private:
        std::string m_time_pattern;
    };


    class ContentFormatItem : public FormatItem {
    public:
        void format(std::ostream &out, LogEvent::ptr ev) override {
            out << ev->getContent();
        }
    };

    class NewLineFormatItem : public FormatItem {
    public:
        void format(std::ostream &out, LogEvent::ptr ev) override {
            out << std::endl;
        }
    };

    class PercentSignFormatItem : public FormatItem {
    public:
        void format(std::ostream &out, LogEvent::ptr ev) override {
            out << '%';
        }
    };

    class TabFormatItem : public FormatItem {
    public:
        void format(std::ostream &out, LogEvent::ptr ev) override {
            out << '\t';
        }
    };

}
/**
 * %p 输出日志等级
 * %f 输出文件名
 * %l 输出行号
 * %d 输出日志时间
 * %t 输出线程号
 * %F 输出协程号
 * %m 输出日志消息
 * %n 输出换行
 * %% 输出百分号
 * %T 输出制表符
 * */


#endif //WYATT_FORMATITEM_H
