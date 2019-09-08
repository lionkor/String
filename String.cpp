#include "String.h"

String::String(const char* cs)
    : m_size(std::strlen(cs)), 
      m_chars(std::make_unique<char[]>(m_size+1))
{
    std::strcpy(m_chars.get(), cs);
}

String::String(const String& str)
    : m_size(str.m_size),
      m_chars(std::make_unique<char[]> (m_size+1))
{
    std::strcpy(m_chars.get(), str.m_chars.get());
}

String::~String()
{
}

String& String::operator=(const String& str)
{
    m_size = str.m_size;
    m_chars = std::make_unique<char[]>(m_size+1);
    std::strcpy(m_chars.get(), str.m_chars.get());
    return *this;
}

String& String::operator=(const char* cs)
{
    m_size = std::strlen(cs);
    m_chars = std::make_unique<char[]>(m_size+1);
    std::strcpy(m_chars.get(), cs);
    return *this;
}

String String::format(const char* fmt, ...)
{
    // FIXME: Rewrite this to use variadic templates.
    String s {};
    va_list args;
    va_start(args, fmt);
    unsigned size = std::vsnprintf (NULL, 0, fmt, args);
    va_end (args);
    s.m_chars = std::make_unique<char[]>(size+1);
    va_start(args, fmt);
    std::vsnprintf (s.m_chars.get(), size + 1, fmt, args);
    va_end (args);
    s.m_size = size;
    return s;
}

