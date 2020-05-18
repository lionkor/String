#include <iostream>
#include "../include/String.h"

#define CATCH_CONFIG_MAIN
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("String::String") {
    REQUIRE_NOTHROW(String());
    REQUIRE_NOTHROW(String(""));
    REQUIRE_NOTHROW(String(nullptr));
    String s0;
    REQUIRE_NOTHROW(String(std::move(s0)));
    REQUIRE_NOTHROW(String(String()));

    String s1;
    REQUIRE(s1.size() == s1.length());
    REQUIRE(s1.size() == 0);

    String s2("Hello");
    REQUIRE(s2.size() == s2.length());
    REQUIRE(s2.size() == 5);
    
    String s3("What a wonderful world");
    String s4(s3.begin() + 7, s3.end() - 6);
    REQUIRE(s4.as_std_string() == "wonderful");
}

TEST_CASE("String::begin and String::end") {
    String s1("Hello, World");
    REQUIRE(*s1.begin() == 'H');
    REQUIRE(*(s1.end() - 1) == 'd');

    const String s2("Bye!");
    REQUIRE(*s2.begin() == 'B');
    REQUIRE(*(s2.end() - 1) == '!');
}

TEST_CASE("String::empty") {
    String s_empty;
    String s_notempty("What a wonderful world!");
    REQUIRE(s_empty.empty());
    REQUIRE_FALSE(s_notempty.empty());
}

TEST_CASE("String::at") {
    String s1("A String");
    REQUIRE(s1.at(0) == 'A');
    REQUIRE(s1.at(s1.size() - 1) == 'g');
    REQUIRE_THROWS(s1.at(-1));
    REQUIRE_THROWS(s1.at(100));
    REQUIRE_THROWS(s1.at(s1.size()));
}

TEST_CASE("String::as_c_string, empty") {
    String s1;
    auto   cstr = s1.as_c_string();
    REQUIRE(std::strcmp(cstr.get(), "") == 0);
}

TEST_CASE("String::as_c_string, not empty") {
    String s1("Hello!");
    auto   cstr = s1.as_c_string();
    REQUIRE(std::strcmp(cstr.get(), "Hello!") == 0);
}

TEST_CASE("String::as_std_string, empty") {
    String      s1;
    std::string str = s1.as_std_string();
    REQUIRE(str.empty());
}

TEST_CASE("String::as_std_string, not empty") {
    String      s1("std string sucks!");
    std::string str = s1.as_std_string();
    REQUIRE(str == "std string sucks!");
}

TEST_CASE("String::insert char, empty") {
    String s1;
    s1.insert(s1.begin(), 'X');
    REQUIRE_NOTHROW(s1.at(0));
    REQUIRE(s1.at(0) == 'X');
}

TEST_CASE("String::insert char, not empty") {
    // insert middle
    String s1("life is pain");
    s1.insert(s1.begin() + 4, 'X');
    REQUIRE_NOTHROW(s1.at(4));
    REQUIRE(s1.at(4) == 'X');
    REQUIRE(s1.as_std_string() == "lifeX is pain");
    // insert end
    s1.insert(s1.end(), 'L');
    REQUIRE(s1.as_std_string() == "lifeX is painL");
    // insert begin
    s1.insert(s1.begin(), 'e');
    REQUIRE(s1.as_std_string() == "elifeX is painL");
    // errors
    REQUIRE_THROWS(s1.insert(s1.end() + 1, 'X'));
}

TEST_CASE("String::insert String, empty") {
    String s1;
    s1.insert(s1.begin(), "XYZ");
    REQUIRE_NOTHROW(s1.at(0));
    REQUIRE(s1.size() == 3);
    REQUIRE(s1.at(0) == 'X');
    REQUIRE(s1.at(1) == 'Y');
    REQUIRE(s1.at(2) == 'Z');
    REQUIRE(s1.as_std_string() == "XYZ");
}

TEST_CASE("String::insert String, not empty") {
    String s1("life is pain");
    // insert middle
    s1.insert(s1.begin() + 4, "XYZ");
    REQUIRE(s1.as_std_string() == "lifeXYZ is pain");
    // insert end
    s1.insert(s1.end(), "lmnop");
    REQUIRE(s1.as_std_string() == "lifeXYZ is painlmnop");
    // insert begin
    s1.insert(s1.begin(), "okok");
    REQUIRE(s1.as_std_string() == "okoklifeXYZ is painlmnop");
    // errors
    REQUIRE_THROWS(s1.insert(s1.end() + 1, "nice"));
}

TEST_CASE("String::insert iters, empty") {
    String s1;
    String s2("hi");
    s1.insert(s1.begin(), s2.begin(), s2.end());
    REQUIRE_NOTHROW(s1.at(0));
    REQUIRE(s1.size() == 2);
    REQUIRE(s1.at(0) == 'h');
    REQUIRE(s1.at(1) == 'i');
    REQUIRE(s1.as_std_string() == "hi");
}

TEST_CASE("String::insert iters, not empty") {
    String s1("life is pain");
    // insert middle
    String s2("XYZ");
    s1.insert(s1.begin() + 4, s2.begin(), s2.end());
    REQUIRE(s1.as_std_string() == "lifeXYZ is pain");
    // insert end
    String s3("lmnop");
    s1.insert(s1.end(), s3.begin(), s3.end());
    REQUIRE(s1.as_std_string() == "lifeXYZ is painlmnop");
    // insert begin
    String s4("okok");
    s1.insert(s1.begin(), s4.begin(), s4.end());
    REQUIRE(s1.as_std_string() == "okoklifeXYZ is painlmnop");
    // errors
    REQUIRE_THROWS(s1.insert(s1.end() + 1, s4.begin(), s4.end()));
}

TEST_CASE("String::clear, empty") {
    String s;
    REQUIRE(s.size() == 0);
    s.clear();
    REQUIRE(s.size() == 0);
}

TEST_CASE("String::clear, not empty") {
    String s("Hello, World");
    REQUIRE(s.size() == 12);
    s.clear();
    REQUIRE(s.size() == 0);
}

TEST_CASE("String::erase iter") {
    String s_empty;
    REQUIRE_THROWS(s_empty.erase(s_empty.begin()));

    String s1("Hello");
    REQUIRE_THROWS(s1.erase(s1.end()));

    s1.erase(s1.begin());
    REQUIRE(s1.as_std_string() == "ello");

    s1.erase(s1.begin() + 1);
    REQUIRE(s1.as_std_string() == "elo");
}

TEST_CASE("String::erase_from_to") {
    String s_empty;
    REQUIRE_THROWS(s_empty.erase_from_to(s_empty.begin(), s_empty.end()));

    String s1("Hello");
    s1.erase_from_to(s1.begin(), s1.end());
    REQUIRE(s1.empty());

    String s2("Hello");
    s2.erase_from_to(s2.begin() + 1, s2.end() - 1);
    REQUIRE(s2.as_std_string() == "Ho");

    String s3("Hello");
    s3.erase_from_to(s3.begin() + 1, s3.begin() + 1);
    REQUIRE(s3.as_std_string() == "Hello");

    REQUIRE_THROWS(s3.erase_from_to(s3.begin() + 3, s3.begin() + 2));
}

TEST_CASE("String::erase_n") {
    String s_empty;
    REQUIRE_THROWS(s_empty.erase_n(s_empty.begin(), 1));

    String s1("Hello");
    s1.erase_n(s1.begin(), s1.size());
    REQUIRE(s1.empty());

    String s2("Hello");
    s2.erase_n(s2.begin() + 1, s2.size() - 2);
    REQUIRE(s2.as_std_string() == "Ho");

    String s3("Hello");
    s3.erase_n(s3.begin() + 1, 0);
    REQUIRE(s3.as_std_string() == "Hello");
}

TEST_CASE("String::substring") {
    String s1("Hello, World!");
    REQUIRE(s1.substring(s1.begin() + 1, s1.end() - 1).as_std_string() == "ello, World");
    
    String s2("Hello, World!");
    REQUIRE(s2.substring(s2.begin() + 1, 4).as_std_string() == "ello");
}
