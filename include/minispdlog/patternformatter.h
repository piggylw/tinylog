#pragma once

#include "formatter.h"
#include "level.h"
#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <ctime>

namespace minispdlog
{

class PatternFormatter : public Formatter
{
public:
    // pattern 示例: "[%Y-%m-%d %H:%M:%S] [%t] [%l] [%n] [%F:%f:%P] %v"
    explicit PatternFormatter(std::string pattern = "[%Y-%m-%d %H:%M:%S] [%t] [%l] [%n] [%F:%f:%P] %v");
    ~PatternFormatter() override = default;

    //实现format接口
    void format(const details::LogMsg& msg, fmt::memory_buffer& dest) override;
    std::unique_ptr<Formatter> clone() const override;
    
    //设置新的格式
    void setPattern(const std::string& pattern);

public:
    //抽象基类:处理单个占位符
    class FlagFormatter
    {
    public:
        virtual ~FlagFormatter() = default;
        virtual void format(const details::LogMsg& msg, const std::tm& time, fmt::memory_buffer& dest) = 0;
        virtual std::unique_ptr<FlagFormatter> clone() const = 0;
    };

private:
    //将pattern编译为FlagFormatter
    void compilePattern();

    std::tm getTime(const details::LogMsg& msg);
    std::string m_pattern;
    std::vector<std::unique_ptr<FlagFormatter>> m_formatters;

    //时间缓存
    std::chrono::seconds m_lastTimeSec{0};
    std::tm m_cachedTm{};
};

}