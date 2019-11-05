project(test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS 2a)

add_executable(test main.cpp String.cpp StringBuilder.cpp StringView.cpp)
