cmake_minimum_required(VERSION 3.11)
project(minispdlog VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

# 使用本地的 fmt 库
add_subdirectory(third_party/fmt)

# 包含子目录
add_subdirectory(src)
add_subdirectory(tests)