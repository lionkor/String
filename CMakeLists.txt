cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_STANDARD 17)

project(StringTest)

add_executable(StringTest
    test/main.cpp
    src/String.cpp
    include/String.h
)

include_directories(StringTest "./src" "./include")
