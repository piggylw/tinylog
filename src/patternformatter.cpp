#include "minispdlog/patternformatter.h"
#include "minispdlog/details/utils.h"
#include <iomanip>
#include <sstream>
#include <cctype>

namespace minispdlog
{

//普通文本
class RawStringFormatter : public PatternFormatter::FlagFormatter
{
public:
    explicit RawStringFormatter(const std::string& str)
        : m_str(str)
    {}

    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        dest.append(m_str.data(), m_str.data() + m_str.size());
    }

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<RawStringFormatter>(m_str);
    }

private:
    std::string m_str;
};

//%Y : 年份
class YearFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        fmt::format_to(std::back_inserter(dest), "{:04}", time.tm_year + 1900);
    }

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<YearFormatter>();
    }
};

//%m : 月份
class MonthFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        fmt::format_to(std::back_inserter(dest), "{:02}", time.tm_mon + 1);
    }

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<MonthFormatter>();
    }
};

//%d : 日期
class DayFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        fmt::format_to(std::back_inserter(dest), "{:02}", time.tm_mday);
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<DayFormatter>();
    }

};

//H : 小时
class HourFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        fmt::format_to(std::back_inserter(dest), "{:02}", time.tm_hour);
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<HourFormatter>();
    }
};

//%M : 分钟
class MinuteFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        fmt::format_to(std::back_inserter(dest), "{:02}", time.tm_min);
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<MinuteFormatter>();
    }
};

//%S : 秒
class SecondFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        fmt::format_to(std::back_inserter(dest), "{:02}", time.tm_sec);
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<SecondFormatter>();
    }
};

//%t : 线程ID
class ThreadIdFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        fmt::format_to(std::back_inserter(dest), "{}", msg.m_threadId);
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<ThreadIdFormatter>();
    }
};

//%l : 日志级别(短格式 I W E C T D)
class LevelShortFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        const char* levelStr = level2ShortString(msg.m_level);
        dest.append(levelStr, levelStr + std::strlen(levelStr));
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<LevelShortFormatter>();
    }
};

//%L : 日志级别(完整格式 INFO WARN ERROR CRITICAL TRACE DEBUG)
class LevelFullFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        const char* levelStr = level2String(msg.m_level);
        dest.append(levelStr, levelStr + std::strlen(levelStr));
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<LevelFullFormatter>();
    }
};

//%n : logger名称
class LoggerNameFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        dest.append(msg.m_loggerName.data(), msg.m_loggerName.data() + msg.m_loggerName.size());
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<LoggerNameFormatter>();
    }
};

//%v : 日志消息内容
class PayloadFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        dest.append(msg.m_payload.data(), msg.m_payload.data() + msg.m_payload.size());
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<PayloadFormatter>();
    }
};

//%F : 源码文件名
class SourceFileFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        dest.append(msg.m_sourceLocation.m_fileName,
                    msg.m_sourceLocation.m_fileName + std::strlen(msg.m_sourceLocation.m_fileName));
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<SourceFileFormatter>();
    }
};

//%f : 源码所在函数
class SourceFunctionFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        dest.append(msg.m_sourceLocation.m_functionName,
                    msg.m_sourceLocation.m_functionName + std::strlen(msg.m_sourceLocation.m_functionName));
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<SourceFunctionFormatter>();
    }
};

//%P : 源码行号
class SourceLineFormatter : public PatternFormatter::FlagFormatter
{
public:
    void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) override
    {
        fmt::format_to(std::back_inserter(dest), "{}", msg.m_sourceLocation.m_line);
    }   

    std::unique_ptr<PatternFormatter::FlagFormatter> clone() const override
    {
        return std::make_unique<SourceLineFormatter>();
    }
};


//PatternFormatter 方法实现
PatternFormatter::PatternFormatter(std::string pattern)
    : m_pattern(std::move(pattern))
{
    compilePattern();
}

void PatternFormatter::format(const details::LogMsg& msg, fmt::memory_buffer& dest)
{
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(msg.m_timePoint.time_since_epoch());
    if (secs != m_lastTimeSec)
    {
        m_cachedTm = getTime(msg);
        m_lastTimeSec = secs;
    }

    for(auto& formatter : m_formatters)
    {
        formatter->format(msg, m_cachedTm, dest);
    }

    dest.push_back('\n');
}

std::unique_ptr<Formatter> PatternFormatter::clone() const
{
    return std::make_unique<PatternFormatter>(m_pattern);
}

void PatternFormatter::setPattern(const std::string& pattern)
{
    m_pattern = pattern;
    m_formatters.clear();
    compilePattern();
}

void PatternFormatter::compilePattern()
{
    auto it = m_pattern.begin();
    auto end = m_pattern.end();
    std::string userChars;

    while(it != end)
    {
        if(*it == '%')
        {
            if(!userChars.empty())
            {
                m_formatters.push_back(std::make_unique<RawStringFormatter>(userChars));
                userChars.clear();
            }

            ++it;

            if(it != end)
            {
                char flag = *it;
                ++it;

                switch(flag)
                {
                    case 'Y':
                        m_formatters.push_back(std::make_unique<YearFormatter>());
                        break;
                    case 'm':
                        m_formatters.push_back(std::make_unique<MonthFormatter>());
                        break;
                    case 'd':
                        m_formatters.push_back(std::make_unique<DayFormatter>());
                        break;
                    case 'H':
                        m_formatters.push_back(std::make_unique<HourFormatter>());
                        break;
                    case 'M':
                        m_formatters.push_back(std::make_unique<MinuteFormatter>());
                        break;
                    case 'S':
                        m_formatters.push_back(std::make_unique<SecondFormatter>());
                        break;
                    case 't':
                        m_formatters.push_back(std::make_unique<ThreadIdFormatter>());
                        break;
                    case 'l':
                        m_formatters.push_back(std::make_unique<LevelShortFormatter>());
                        break;
                    case 'L':
                        m_formatters.push_back(std::make_unique<LevelFullFormatter>());
                        break;
                    case 'n':
                        m_formatters.push_back(std::make_unique<LoggerNameFormatter>());
                        break;
                    case 'v':
                        m_formatters.push_back(std::make_unique<PayloadFormatter>());
                        break;
                    case 'F':
                        m_formatters.push_back(std::make_unique<SourceFileFormatter>());
                        break;
                    case 'f':
                        m_formatters.push_back(std::make_unique<SourceFunctionFormatter>());
                        break;
                    case 'P':
                        m_formatters.push_back(std::make_unique<SourceLineFormatter>());
                        break;
                    default:
                        //未知标志，忽略
                        break;
                }
            }
        }
        else
        {
            userChars += *it;
            ++it;
        }
    }

    if(!userChars.empty())
    {
        m_formatters.push_back(std::make_unique<RawStringFormatter>(userChars));
    }
}

std::tm PatternFormatter::getTime(const details::LogMsg& msg)
{
    auto timeT = LogClock::to_time_t(msg.m_timePoint);
    std::tm tmVal;
    localtime_r(&timeT, &tmVal);
    return tmVal;
}

}//minispdlog