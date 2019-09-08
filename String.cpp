#include "String.h"

String::String(const char* cs)
{
    m_size = std::strlen(cs);
    m_chars = new char[m_size + 1]; // + 1 for '\0'
    std::strcpy(m_chars, cs);
}

String::String(const String& str)
{
    m_size = str.m_size;
    m_chars = new char[m_size + 1];
    std::strcpy(m_chars, str.m_chars);
}

String::~String()
{
    if (m_chars) delete[] m_chars;
}

String& String::operator=(const String& str)
{
    if (m_chars) delete[] m_chars;
    m_size = str.m_size;
    m_chars = new char[m_size + 1];
    std::strcpy(m_chars, str.m_chars);
    return *this;
}

String& String::operator=(const char* cs)
{
    if (m_chars) delete[] m_chars;
    m_size = std::strlen(cs);
    m_chars = new char[m_size + 1];
    std::strcpy(m_chars, cs);
    return *this;
}

String String::format(const char* fmt, ...)
{
    String s {};
    va_list args;
    va_start(args, fmt);
    unsigned size = std::vsnprintf (NULL, 0, fmt, args);
    va_end (args);
    s.m_chars = new char[size + 1];
    va_start(args, fmt);
    std::vsnprintf (s.m_chars, size + 1, fmt, args);
    va_end (args);
    s.m_size = size;
    return s;
}

