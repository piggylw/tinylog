# 测试1:日志级别测试
add_executable(testlevel test_level.cpp)
target_link_libraries(testlevel PRIVATE minispdlog)