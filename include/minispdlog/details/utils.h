#pragma once

#include "../common.h"
#include <string>
#include <thread>
#include <pthread.h>

namespace minispdlog
{
namespace details
{
    std::string formatTime(
        const LogClock::time_point& tp,
        const char* format = "%Y-%m-%d %H:%M:%S"
    );

    int64_t getTimeStampMillis();
    size_t getThreadId();
    
    // std::string& ltrim(std::string& s);
    // std::string& rtrim(std::string& s);
    // std::string& trim(std::string& s);

}   
}