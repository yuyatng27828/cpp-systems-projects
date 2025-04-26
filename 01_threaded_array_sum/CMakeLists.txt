cmake_minimum_required(VERSION 3.10)

project(ThreadedArraySum VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_executable(threaded_array_sum src/main.cpp)

target_include_directories(threaded_array_sum PRIVATE include)