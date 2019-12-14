cmake_minimum_required(VERSION 3.15)

project(String)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_EXTENSIONS 2a)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -fPIC -s")

add_library(String STATIC
    src/String.cpp
    src/StringView.cpp
    src/StringBuilder.cpp
    include/Core.h
    include/Exceptions.h
    include/String.h
    include/StringBuilder.h
    include/StringView.h
)

include_directories(String "./src" "./include")

