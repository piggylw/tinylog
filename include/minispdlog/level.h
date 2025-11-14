#pragma once

#include "common.h"
#include <string>

namespace minispdlog
{

    enum class level
    {
        trace = 0,
        debug = 1,
        info  = 2,
        warn  = 3,
        error   = 4,
        critical = 5,
        off   = 6
    };

    const char* level2String(level lv);
    const char* level2ShortString(level lv);
    level string2Level(const std::string& str);
    bool logLevelEnabled(level loggerLevel, level msgLevel);

}