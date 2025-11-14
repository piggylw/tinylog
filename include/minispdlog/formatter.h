#pragma once

#include "common.h"
#include "details/logmsg.h"
#include <fmt/format.h>
#include <memory>

namespace minispdlog
{

class Formatter
{
public:
    virtual ~Formatter() = default;
    virtual void format(const details::LogMsg& msg, fmt::memory_buffer& dest) = 0;
    virtual std::unique_ptr<Formatter> clone() const = 0;
};

}