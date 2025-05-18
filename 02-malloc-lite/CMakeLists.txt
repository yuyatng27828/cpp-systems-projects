cmake_minimum_required(VERSION 3.10)

project(MallocLite VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_executable(malloc_lite src/main.cpp)

target_include_directories(malloc_lite PRIVATE include)
target_compile_options(malloc_lite PRIVATE -fsanitize=address -g)
target_link_options(malloc_lite PRIVATE -fsanitize=address)
