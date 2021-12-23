//
// Created by Administrator on 2021/12/14.
//

#include "LogFormatter.h"



wyatt::LogFormatter::LogFormatter(std::string pattern) {
    // %d {%d:%d} aaaaaa %d %n
    enum PARSE_STATUS {
        SCAN_STATUS,   // 扫描普通字符
        CREATE_STATUS, // 扫描到 %，处理占位符
    };
    PARSE_STATUS STATUS = SCAN_STATUS;
    size_t str_begin = 0, str_end = 0;
    //    std::vector<char> item_list;
    for (size_t i = 0; i < pattern.length(); i++) {
        switch (STATUS) {
            case SCAN_STATUS: // 普通扫描分支，将扫描到普通字符串创建对应的普通字符处理对象后填入 m_format_item_list 中
                // 扫描记录普通字符的开始结束位置
                str_begin = i;
                for (str_end = i; str_end < pattern.length(); str_end++) {
                    // 扫描到 % 结束普通字符串查找，将 STATUS 赋值为占位符处理状态，等待后续处理后进入占位符处理状态
                    if (pattern[str_end] == '%') {
                        STATUS = CREATE_STATUS;
                        break;
                    }
                }
                i = str_end;
                formatItemList.push_back(
                        std::make_shared<PlainFormatItem>(
                                pattern.substr(str_begin, str_end - str_begin)));
                break;

            case CREATE_STATUS: // 处理占位符
//                assert(!formatItemMap.empty() && "format_item_map 没有被正确的初始化");
                auto itor = formatItemMap.find(pattern[i]);
                if (itor == formatItemMap.end()) {
                    formatItemList.push_back(std::make_shared<PlainFormatItem>("<error format>"));
                } else {
                    formatItemList.push_back(itor->second);
                }
                STATUS = SCAN_STATUS;
                break;
        }
    }

}



std::string wyatt::LogFormatter::format(LogEvent::ptr ev)
{
    std::stringstream ss;
    for (auto& item : formatItemList)
    {
        item->format(ss, ev);
    }
    return ss.str();
}
