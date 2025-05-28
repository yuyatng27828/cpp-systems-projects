cmake_minimum_required(VERSION 3.16)
project(redis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_compile_options(-fsanitize=address -g -Wall -Wextra -Wpedantic)
add_link_options(-fsanitize=address)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_executable(redis
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/redis.cpp
)

target_include_directories(redis PRIVATE ${INCLUDE_DIR})
