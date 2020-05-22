cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Weverything -Wno-c++98-compat -Wno-c++98-c++11-compat-binary-literal -Wno-c++98-compat-pedantic --pedantic -Wimplicit-fallthrough -Wno-global-constructors -Wno-exit-time-destructors -Wno-shadow-field-in-constructor -Wno-padded -Wno-extra-semi")

project(StringTest)

add_executable(StringTest
    test/main.cpp
    src/String.cpp
    include/String.h
)

include_directories(StringTest "./src" "./include")
