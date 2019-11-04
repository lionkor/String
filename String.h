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
    static constexpr unsigned short MAX_ALLOC = 23;

    friend class StringBuilder;
    using Iterator = const char*;

    String();
    String(const char*);
    String(const Iterator start, const Iterator end);
    String(const String&);
    static String format(const char* fmt, ...);

    virtual ~String();

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

    inline std::size_t size() const
    {
        return m_chars.all.dynamic ? m_chars.heap.size : m_chars.stack.size;
    }

    inline const char* c_str() const { return m_chars.all.dynamic ? m_chars.heap.data : m_chars.stack.data; }
    friend std::ostream& operator<<(std::ostream& os, const String& str)
    {
        return os << str.chars();
    }
    
private:
    inline void set_size(std::size_t size)
    {
        if (m_chars.all.dynamic)
            m_chars.heap.size = size;
        else
            m_chars.stack.size = size;
    }

    inline const char* chars() const 
    {
        return m_chars.all.dynamic ? m_chars.heap.data : m_chars.stack.data;
    }

    inline char*& chars()
    {
        if (m_chars.all.dynamic)
        {
            return m_chars.heap.data;
        }
        else
        {
            m_chars.heap.data = m_chars.stack.data;
            return m_chars.heap.data;
        }
    }
    
    union MainDataUnion {
        MainDataUnion() {}
        struct
        {
            unsigned char dynamic : 1;
        } all;
        struct
        {
            unsigned char dynamic : 1 = 1;
            std::size_t size : std::numeric_limits<std::size_t>::digits - 1;
            // FIXME: Implement capacity
            char* data;
        } heap;
        struct
        {
            unsigned char dynamic : 1 = 0;
            unsigned char size : std::numeric_limits<unsigned char>::digits - 1;
            char data[MAX_ALLOC];
        } stack;
    } m_chars;
};

#endif // STRING_H
