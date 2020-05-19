#include <iostream>
#include <iomanip>
#include "../include/String.h"
//*
int main() {
    String::Format fmt;
    fmt.precision    = 3;
    fmt.width        = 10;
    fmt.alignment    = String::Format::Align::Right;
    String my_string = String::format(fmt, 3.53214, "|", fmt, 5.2436, "|");
    std::cout << my_string << std::endl;
}
//*/

/*

#define CATCH_CONFIG_MAIN
#include "Catch2/single_include/catch2/catch.hpp"

TEST_CASE("String::format") {
    REQUIRE(String::format("Hello") == "Hello");
    REQUIRE(String::format("Hello ", "World") == "Hello World");
    REQUIRE(String::format(1, 2, 3) == "123");
    REQUIRE(String::format(1.0) == "1");
    
    String::Format fmt;
    fmt.precision = 1;
    REQUIRE(String::format(fmt, 1.0/3.0) == "0.3");
    fmt.precision = 2;
    REQUIRE(String::format(fmt, 1.0/3.0) == "0.33");
    fmt.base = String::Format::Base::Hex;
    REQUIRE(String::format(fmt, 0xf) == "f");
    fmt.base = String::Format::Base::Oct;
    REQUIRE(String::format(fmt, 03562) == "3562");
    REQUIRE(String::format(fmt, 10) == "12");
    
    String::Format fmt2;
    fmt2.width = 4;
    REQUIRE(String::format(fmt2, "12", fmt2, "5") == "12  5   ");
    fmt2.alignment = String::Format::Alignment::Right;
    REQUIRE(String::format(fmt2, "12", fmt2, "5") == "  12   5");
    fmt2.fill = '-';
    REQUIRE(String::format(fmt2, "12", fmt2, "5") == "--12---5");
    
    REQUIRE(String::format(String(), String()) == "");
    std::string s("Hello");
    REQUIRE(String::format(s, String("World")) == "HelloWorld");
    const char* cstr = "Wonder";
    REQUIRE(String::format(cstr, "ful day") == "Wonderful day");
    REQUIRE(String::format("My name is ", "String", " and my age is ", 560) == "My name is String and my age is 560");
}

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
    REQUIRE(s4 == "wonderful");

    String s5('v');
    REQUIRE(s5 == "v");
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

TEST_CASE("String::erase from to") {
    String s_empty;
    REQUIRE_THROWS(s_empty.erase(s_empty.begin(), s_empty.end()));

    String s1("Hello");
    s1.erase(s1.begin(), s1.end());
    REQUIRE(s1.empty());

    String s2("Hello");
    s2.erase(s2.begin() + 1, s2.end() - 1);
    REQUIRE(s2.as_std_string() == "Ho");

    String s3("Hello");
    s3.erase(s3.begin() + 1, s3.begin() + 1);
    REQUIRE(s3.as_std_string() == "Hello");

    REQUIRE_THROWS(s3.erase(s3.begin() + 3, s3.begin() + 2));
}

TEST_CASE("String::erase n") {
    String s_empty;
    REQUIRE_THROWS(s_empty.erase(s_empty.begin(), 1));

    String s1("Hello");
    s1.erase(s1.begin(), s1.size());
    REQUIRE(s1.empty());

    String s2("Hello");
    s2.erase(s2.begin() + 1, s2.size() - 2);
    REQUIRE(s2.as_std_string() == "Ho");

    String s3("Hello");
    s3.erase(s3.begin() + 1, 0);
    REQUIRE(s3.as_std_string() == "Hello");
}

TEST_CASE("String::substring") {
    String s1("Hello, World!");
    REQUIRE(s1.substring(s1.begin() + 1, s1.end() - 1).as_std_string() == "ello, World");

    String s2("Hello, World!");
    REQUIRE(s2.substring(s2.begin() + 1, 4).as_std_string() == "ello");
}

TEST_CASE("String::find") {
    String s1("Hello");
    REQUIRE(s1.find('H') == s1.begin());
    REQUIRE(s1.find('X') == s1.end());
    REQUIRE(s1.find('e') == s1.begin() + 1);
    REQUIRE(s1.find('E') == s1.end());
    REQUIRE(s1.find('o') == s1.end() - 1);

    const String s2("Hello");
    REQUIRE(s2.find('H') == s2.begin());
    REQUIRE(s2.find('X') == s2.end());
    REQUIRE(s2.find('e') == s2.begin() + 1);
    REQUIRE(s2.find('E') == s2.end());
    REQUIRE(s2.find('o') == s2.end() - 1);
}

TEST_CASE("String::find_caseless") {
    String s1("Hello");
    REQUIRE(s1.find_caseless('H') == s1.begin());
    REQUIRE(s1.find_caseless('X') == s1.end());
    REQUIRE(s1.find_caseless('e') == s1.begin() + 1);
    REQUIRE(s1.find_caseless('E') == s1.begin() + 1);
    REQUIRE(s1.find_caseless('O') == s1.end() - 1);

    const String s2("Hello");
    REQUIRE(s2.find_caseless('H') == s2.begin());
    REQUIRE(s2.find_caseless('X') == s2.end());
    REQUIRE(s2.find_caseless('e') == s2.begin() + 1);
    REQUIRE(s2.find_caseless('E') == s2.begin() + 1);
    REQUIRE(s2.find_caseless('O') == s2.end() - 1);
}

TEST_CASE("String::equals") {
    REQUIRE(String("Hello").equals(String("Hello")));
    REQUIRE(String("").equals(String("")));
    REQUIRE(String().equals(String("")));
    REQUIRE(String().equals(String()));
    REQUIRE(String("\0\0").equals(String("")));
    REQUIRE_FALSE(String("HELL").equals(String("hell")));
    REQUIRE_FALSE(String("").equals(String(" ")));
}

TEST_CASE("String::operator==") {
    REQUIRE(String("Hello") == String("Hello"));
    REQUIRE(String("") == String(""));
    REQUIRE(String() == String(""));
    REQUIRE(String() == String());
    REQUIRE(String("\0\0") == String(""));

    REQUIRE(String("HELL") != String("hell"));
    REQUIRE(String("") != String(" "));
    REQUIRE(String(".") != String(".."));
    REQUIRE(String("Aa") != String("A"));

    REQUIRE(String("Hello") == "Hello");
    REQUIRE(String() == "");
}

TEST_CASE("String::operator+=") {
    String s;
    s += "Hello ";
    s += "World!";
    REQUIRE(s == "Hello World!");

    String s2("such is ");
    REQUIRE((s2 += "life") == "such is life");
}

TEST_CASE("String::operator+") {
    String s1("Hello there");
    String s2("my friend!");
    String s3 = s1 + ", " + s2;
    REQUIRE(s3 == "Hello there, my friend!");
    REQUIRE(s1 + String() == s1);
}

TEST_CASE("String::replace String") {
    String s("abcdabcdabcdabcd");
    s.replace("ab", "XX");
    REQUIRE(s == "XXcdXXcdXXcdXXcd");

    String s2;
    s2.replace("", "Hello");
    REQUIRE(s2 == "");
    
    String s3("hello hello");
    REQUIRE_THROWS(s3.replace("hello", "hello hello"));
}

TEST_CASE("String::replace char") {
    String s("abcdabcdabcdabcd");
    s.replace('a', 'X');
    REQUIRE(s == "XbcdXbcdXbcdXbcd");
}

TEST_CASE("String::replace n Strings") {
    String s("hello world hello world hello world");
    s.replace("hello world", "bye bye", 2);
    REQUIRE(s == "bye bye bye bye hello world");

    String s2("a b a b a b");
    s2.replace("a b", "XXX", 0);
    REQUIRE(s2 == "a b a b a b");

    String s3("abcabcabc");
    s3.replace("abc", "ABC", 100);
    REQUIRE(s3 == "ABCABCABC");
}

TEST_CASE("String::find String") {
    {
        // normal
        String s("Hello, World!");
        REQUIRE(s.find("nope") == s.end());
        REQUIRE(s.find("Hello") == s.begin());
        REQUIRE(s.find("!") == s.end() - 1);
        REQUIRE(s.find("Hello, World!") == s.begin());
        REQUIRE(s.find("llo") == s.begin() + 2);
        REQUIRE_FALSE(s.find("") == s.end());
    }
    {
        // const
        const String s("Hello, World!");
        REQUIRE(s.find("nope") == s.end());
        REQUIRE(s.find("Hello") == s.begin());
        REQUIRE(s.find("!") == s.end() - 1);
        REQUIRE(s.find("Hello, World!") == s.begin());
        REQUIRE(s.find("llo") == s.begin() + 2);
        REQUIRE_FALSE(s.find("") == s.end());
    }
    {
        // normal with start
        String s("Hello, World!");
        REQUIRE(s.find("nope", s.begin()) == s.end());
        REQUIRE(s.find("Hello", s.begin()) == s.begin());
        REQUIRE(s.find("!", s.begin()) == s.end() - 1);
        REQUIRE(s.find("Hello, World!", s.begin()) == s.begin());
        REQUIRE(s.find("llo", s.begin()) == s.begin() + 2);
        REQUIRE_FALSE(s.find("", s.begin()) == s.end());
        REQUIRE(s.find("Hello", s.begin() + 6) == s.end());
        REQUIRE(s.find("World", s.begin() + 5) == s.begin() + 7);
    }
    {
        // const with start
        const String s("Hello, World!");
        REQUIRE(s.find("nope", s.begin()) == s.end());
        REQUIRE(s.find("Hello", s.begin()) == s.begin());
        REQUIRE(s.find("!", s.begin()) == s.end() - 1);
        REQUIRE(s.find("Hello, World!", s.begin()) == s.begin());
        REQUIRE(s.find("llo", s.begin()) == s.begin() + 2);
        REQUIRE_FALSE(s.find("", s.begin()) == s.end());
        REQUIRE(s.find("Hello", s.begin() + 6) == s.end());
        REQUIRE(s.find("World", s.begin() + 5) == s.begin() + 7);
    }
}

TEST_CASE("String::contains") {
    REQUIRE(String("Hello").contains("Hello"));
    REQUIRE(String("Hello").contains("ello"));
    REQUIRE(String("Hello").contains("Hell"));
    REQUIRE(String("Hello").contains("ell"));
    REQUIRE(String("Hello").contains("o"));
    REQUIRE_FALSE(String("Hello").contains("hello"));
    REQUIRE_FALSE(String("Hello").contains("HELLO"));
    REQUIRE_FALSE(String("Hello").contains("HH"));
    REQUIRE_FALSE(String("Hello").contains("oo"));
}

TEST_CASE("String::startswith") {
    REQUIRE(String("Hello").startswith("Hello"));
    REQUIRE(String("Hello").startswith("Hell"));
    REQUIRE(String("Hello").startswith("Hel"));
    REQUIRE(String("Hello").startswith("He"));
    REQUIRE(String("Hello").startswith("H"));
    REQUIRE_FALSE(String("Hello").startswith("HH"));
    REQUIRE_FALSE(String("Hello").startswith("ello"));
    REQUIRE_FALSE(String("Hello").startswith("o"));
    REQUIRE_FALSE(String("Hello").startswith("e"));
    REQUIRE_FALSE(String("Hello").startswith("h"));
}

TEST_CASE("String::endswith") {
    REQUIRE(String("Hello").endswith("Hello"));
    REQUIRE(String("Hello").endswith("ello"));
    REQUIRE(String("Hello").endswith("llo"));
    REQUIRE(String("Hello").endswith("lo"));
    REQUIRE(String("Hello").endswith("o"));
    REQUIRE_FALSE(String("Hello").endswith("Hell"));
    REQUIRE_FALSE(String("Hello").endswith("Hel"));
    REQUIRE_FALSE(String("Hello").endswith("l"));
}

TEST_CASE("String::reserve and String::capacity") {
    REQUIRE(String().capacity() == 0);
    String s("Hello, World");
    REQUIRE(s.capacity() == s.size());
    s.reserve(100);
    REQUIRE(s.capacity() == 100);
    s += " WOOOO! Adding bytes!";
    REQUIRE(s.capacity() == 100);
}

TEST_CASE("String::shrink_to_fit") {
    // not testable, implementation defined. just make sure it doesn't crash.
    String s("hello");
    s.reserve(100);
    s.shrink_to_fit();
    REQUIRE(s == "hello");
}

//*/
