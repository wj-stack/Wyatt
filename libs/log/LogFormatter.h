//
// Created by Administrator on 2021/12/14.
//

#ifndef WYATT_LOGFORMATTER_H
#define WYATT_LOGFORMATTER_H


#include <string>
#include <vector>
#include <map>
#include "FormatItem.h"
#include <sstream>

namespace wyatt{

    class LogFormatter {
    private:
        std::vector<FormatItem::ptr> formatItemList; // 格式化字符串解析后的解析器列表
        std::map<char,FormatItem::ptr>formatItemMap{
            {'p' , FormatItem::ptr(new LevelFormatItem)},
            {'f' , FormatItem::ptr(new FilenameFormatItem)},
            {'l' , FormatItem::ptr(new LineFormatItem)},
            {'d' , FormatItem::ptr(new TimeFormatItem)},
            {'t' , FormatItem::ptr(new ThreadIDFormatItem)},
            {'F' , FormatItem::ptr(new FiberIDFormatItem)},
            {'m' , FormatItem::ptr(new ContentFormatItem)},
            {'n' , FormatItem::ptr(new NewLineFormatItem)},
            {'%' , FormatItem::ptr(new PercentSignFormatItem)},
            {'T' , FormatItem::ptr(new TabFormatItem)},
            };
    public:
        typedef std::shared_ptr<LogFormatter> ptr;

        explicit LogFormatter(std::string pattern);
        std::string format(LogEvent::ptr ev);

    };

}

#endif //WYATT_LOGFORMATTER_H
