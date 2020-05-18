#include <iostream>
#include "../include/String.h"

//#define CATCH_CONFIG_MAIN
//#include "Catch2/single_include/catch2/catch.hpp"

int main() {
    String str("Hello, World!");
    std::cout << "_" << str.as_c_string().get() << "_" << std::endl;
    str.insert(str.begin() + 5, 'X');
    std::cout << "_" << str.as_c_string().get() << "_" << std::endl;
    str.insert(str.begin() + 10, " - oh wow, gay shit - ");
    std::cout << "_" << str.as_c_string().get() << "_" << std::endl;
}
