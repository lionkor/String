cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

project(StringTest)

add_executable(StringTest
    test/main.cpp
    src/String.cpp
    include/String.h
)

include_directories(StringTest "./src" "./include")

project(String) 

add_library(String STATIC
    src/String.cpp
    include/String.h
)

include_directories(StringTest "./src" "./include")
