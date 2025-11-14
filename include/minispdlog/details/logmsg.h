#pragma once

#include "../common.h"
#include "../level.h"
#include "utils.h"
#include <string>
#include <cstddef>

namespace minispdlog {
namespace details{

struct SourceLocation
{
    constexpr SourceLocation() = default;

    constexpr SourceLocation(const char* file, int line, const char* function) 
        : m_fileName(file), m_line(line), m_functionName(function) {}

    constexpr bool empty() const noexcept { return m_line == 0; }

    const char* m_fileName{nullptr};
    int m_line{0};
    const char* m_functionName{nullptr};
};
    
struct LogMsg
{
    LogMsg() = default;

    //完整日志消息
    LogMsg(
        StringView loggerName,
        level lv,
        LogClock::time_point tp,
        SourceLocation srcLoc,
        StringView payload
    )
        : m_loggerName(loggerName),
          m_level(lv),
          m_timePoint(tp),
          m_threadId(getThreadId()),
          m_sourceLocation(srcLoc),
          m_payload(payload)
    {}

    // 简化构造函数(自动获取当前时间)
    LogMsg(
        StringView loggerName,
        level lv,
        SourceLocation srcLoc,
        StringView payload
    )
        : LogMsg(
            loggerName,
            lv,
            LogClock::now(),
            srcLoc,
            payload
        )
    {}

    // 最简化构造(无源码位置信息)
    LogMsg(
        StringView loggerName,
        level lv,
        StringView payload
    )  
        : LogMsg(
            loggerName,
            lv,
            SourceLocation(),
            payload
        )
    {}

    LogMsg(const LogMsg&) = default;
    LogMsg& operator=(const LogMsg&) = default;

    StringView m_loggerName;
    minispdlog::level m_level{minispdlog::level::info};
    LogClock::time_point m_timePoint;
    size_t m_threadId{0};
    SourceLocation m_sourceLocation;
    StringView m_payload;
};

}
}