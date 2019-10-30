#ifndef STRING_H
#define STRING_H

#include <cstdarg>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "Core.h"

class String
{
public:
    friend class StringBuilder;
    using Iterator = char*;
    using ConstIterator = const char*;

    String(const char*);
    String(ConstIterator start, ConstIterator end);
    String(const String&);
    static String format(const char* fmt, ...);

    virtual ~String();

    String& operator=(const String&);
    String& operator=(const char*);

    std::size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }

    std::vector<String> split(char delim) const;

    Iterator begin();
    Iterator end();

    ConstIterator begin() const;
    ConstIterator end() const;

    String substring(std::size_t position, std::size_t n) const;
    String substring(ConstIterator begin, ConstIterator end) const;

    [[deprecated]] String substr(std::size_t pos, std::size_t n) const;
    [[deprecated]] String substr(ConstIterator begin,
                                 ConstIterator end) const;
    String trim(char trim = ' ') const;

    const char* c_str() const { return m_chars.get(); }
    friend std::ostream& operator<<(std::ostream& os, const String& str) { return os << str.m_chars.get(); }

private:
    std::size_t m_size;
    std::unique_ptr<char[]> m_chars;
    String() {}
};

#endif // STRING_H
