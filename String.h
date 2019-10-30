#ifndef STRING_H
#define STRING_H

#include <cstdarg>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "Core.h"
#include "StringView.h"

class String
{
public:
    friend class StringBuilder;
    using Iterator = char*;

    String(const char*);
    String(const Iterator start, const Iterator end);
    String(const String&);
    static String format(const char* fmt, ...);

    virtual ~String();

    String& operator=(const String&);
    String& operator=(const char*);

    inline std::size_t size() const { return m_size; }
    inline bool empty() const { return m_size == 0; }

    std::vector<String> split(char delim) const;

    Iterator begin() const;
    Iterator end() const;

    String substring(std::size_t position, std::size_t n) const;
    String substring(const Iterator begin, const Iterator end) const;

    [[deprecated("use substring instead")]] 
    String substr(std::size_t pos, std::size_t n) const;
    
    [[deprecated("use substring instead")]] 
    String substr(const Iterator begin, const Iterator end) const;

    String trim(char trim = ' ') const;
    inline StringView as_string_view() const { return StringView(*this); }

    inline const char* c_str() const { return m_chars.get(); }
    friend std::ostream& operator<<(std::ostream& os, const String& str)
    {
        return os << str.m_chars.get();
    }

private:
    std::size_t m_size;
    std::unique_ptr<char[]> m_chars;
    String() {}
};

#endif // STRING_H
