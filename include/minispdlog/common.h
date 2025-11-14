#pragma once

#include <string>
#include <memory>
#include <cstdint>
#include <chrono>

namespace minispdlog
{

    constexpr const char* VERSION = "0.1.0";
    using StringView = std::string_view;
    using LogClock = std::chrono::system_clock;

}