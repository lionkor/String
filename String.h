#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
#include <cstdarg>

#include "Core.h"

class String
{
public:
    friend class StringBuilder;
    
    String(const char*);
    String(const String&);
    virtual ~String();
    
    String& operator=(const String&);
    
    std::size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }
    
    const char* c_str() const { return m_chars; }
    
    static String format(const char* fmt, ...);
    
    friend std::ostream& operator<<(std::ostream& os, const String& str)
    {
        return os << str.m_chars;
    }
private:
    char* m_chars;
    std::size_t m_size;
    String () {}
};

#endif // STRING_H
