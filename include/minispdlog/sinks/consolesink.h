#pragma once

#include "basesink.h"
#include <iostream>
#include <mutex>

namespace minispdlog {
namespace sinks {

template<typename ConsoleMutex>
class ConsoleSink : public BaseSink<ConsoleMutex>
{
public:
    ConsoleSink() = default;
    ~ConsoleSink() override = default;

protected:
    void sinkLog(const details::LogMsg& msg) override
    {
        fmt::memory_buffer formattedMsg;
        this->formatMessage(msg, formattedMsg);
        std::cout.write(formattedMsg.data(), formattedMsg.size());
    }
    
    void sinkFlush() override
    {
        std::cout << std::flush;
    }

};

using ConsoleSinkMT = ConsoleSink<std::mutex>;
using ConsoleSinkST = ConsoleSink<NullMutex>;

template<typename ConsoleMutex>
class StderrSink : public BaseSink<ConsoleMutex>
{
public:
    StderrSink() = default;
    ~StderrSink() override = default;

protected:
    void sinkLog(const details::LogMsg& msg) override
    {
        fmt::memory_buffer formattedMsg;
        this->formatMessage(msg, formattedMsg);
        std::cerr.write(formattedMsg.data(), formattedMsg.size());
    }

    void sinkFlush() override
    {
        std::cerr << std::flush;
    }
};

using StderrSinkMT = StderrSink<std::mutex>;
using StderrSinkST = StderrSink<NullMutex>;

} // namespace sinks
} // namespace minispdlog