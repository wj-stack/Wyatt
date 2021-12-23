#ifndef WYATT_LOGLEVEL_H
#define WYATT_LOGLEVEL_H

#include <string>

namespace wyatt{

    class LogLevel {
    public:
        enum Level {
            UNKNOWN, // 未知
            DEBUG, // 调试
            INFO, // 信息
            WARN, // 警告
            ERROR, // 错误
            FATAL // 致命错误
        };

        static std::string levelToString(Level level);
    };

}

#endif //WYATT_LOGLEVEL_H
