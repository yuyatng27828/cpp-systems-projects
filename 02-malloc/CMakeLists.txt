cmake_minimum_required(VERSION 3.16)
project(malloc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_compile_options(-fsanitize=address -g -Wall -Wextra -Wpedantic)
add_link_options(-fsanitize=address)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_executable(malloc
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/malloc.cpp
)

target_include_directories(malloc PRIVATE ${INCLUDE_DIR})
