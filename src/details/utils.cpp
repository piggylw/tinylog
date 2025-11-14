#include "minispdlog/details/utils.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cctype>

std::string minispdlog::details::formatTime(const LogClock::time_point &tp, const char *format)
{
    auto timeVal = LogClock::to_time_t(tp);
    std::tm tmVal;
    localtime_r(&timeVal, &tmVal);
    
    std::ostringstream oss;
    oss << std::put_time(&tmVal, format);
    return oss.str();
}

int64_t minispdlog::details::getTimeStampMillis()
{
    auto now = LogClock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

size_t minispdlog::details::getThreadId()
{
    return static_cast<size_t>(pthread_self());
}

