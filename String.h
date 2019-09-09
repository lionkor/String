#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
#include <cstdarg>
#include <memory>

#include "Core.h"

class String
{
public:
    friend class StringBuilder;
    
    String(const char*);
    String(const String&);
    virtual ~String();
    
    String& operator=(const String&);
    String& operator=(const char*);
    
    std::size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }
    
    /// Construct a String instance from a format string.
    static String format(const char* fmt, ...);
    
    const char* c_str() const { return m_chars.get(); }
    friend std::ostream& operator<<(std::ostream& os, const String& str)
    {
        return os << str.m_chars.get();
    }
private:
    std::size_t m_size;
    std::unique_ptr<char[]> m_chars;
    String () {}
};

#endif // STRING_H
