#ifndef STRING_H
#define STRING_H

#include <cstdarg>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "Core.h"
#include "DynamicString.h"
#include "StringView.h"
#include "StringBuilder.h"

class String : public DynamicString
{
public:
    friend class StringBuilder;
    using Iterator = const char*;

    String();
    String(const char*);
    String(const Iterator start, const Iterator end);
    String(const String&);
    String(const StringView&);

    virtual ~String() {}

    String& operator=(const String&);
    String& operator=(const char*);

    bool operator==(const String&) const;
    bool operator==(const char*) const;

    inline bool operator!=(const String& other) const { return !(*this == other); }
    inline bool operator!=(const char* other) const { return !(*this == other); }

    inline char operator[](const std::size_t index) const { return chars()[index]; }

    inline bool empty() const { return size() == 0; }

    std::vector<String> split(char delim) const;

    Iterator begin() const;
    Iterator end() const;

    String substring(std::size_t position, std::size_t n) const;
    String substring(const Iterator begin, const Iterator end) const;

    [[deprecated("use substring instead")]] String substr(std::size_t pos,
                                                          std::size_t n) const;

    [[deprecated("use substring instead")]] String substr(const Iterator begin,
                                                          const Iterator end) const;

    String trim(char trim = ' ') const;
    inline StringView as_string_view() const { return StringView(*this); }

    inline const char* c_str() const
    {
        return m_chars.all.dynamic ? m_chars.heap.data : m_chars.stack.data;
    }
    friend std::ostream& operator<<(std::ostream& os, const String& str)
    {
        return os << str.chars();
    }
    
    template<typename... _Args>
    [[nodiscard]] static String format(StringBuilder& sb)
    {
        return sb.build();
    }
    
    template<typename _T, typename... _Args>
    static String format(StringBuilder&& sb, _T&& t)
    {
        sb.append(t);
        return String::format(sb);
    }
    
    template<typename _T, typename... _Args>
    static String format(StringBuilder&& sb, _T&& t, _Args&&... args)
    {
        sb.append(t);
        return String::format(std::move(sb), args...);
    }
    
    template<typename... _Args>
    static String format(_Args&&... args)
    {
        StringBuilder sb;
        return format(std::move(sb), args...);
    }
};

#include "StringFormatting.h"

#endif // STRING_H
