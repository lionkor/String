#include "StringBuilder.h"
#include "Exceptions.h"

StringBuilder::StringBuilder()
{
    m_chars = new char[1];
    std::strcpy(m_chars, "");
    m_size = 0;
}

StringBuilder::StringBuilder(const StringBuilder& builder)
{
    m_chars = new char[builder.m_size + 1];
    std::strcpy(m_chars, builder.m_chars);
    m_size = builder.m_size;
}

StringBuilder::~StringBuilder()
{
    if (m_chars) delete[] m_chars;
}

void StringBuilder::append(const char* cstr)
{
    if (m_built) throw InvalidAppendAfterBuild();
    char* new_chars = new char[m_size + std::strlen(cstr) + 1];
    if (m_size != 0)
    {
        std::strcpy(new_chars, m_chars);
        std::strcat(new_chars, cstr);
    }
    else
    {
        std::strcpy(new_chars, cstr);
    }
    if (m_chars) delete[] m_chars;
    m_chars = new_chars;
    m_size = std::strlen(m_chars);
}

void StringBuilder::append(char c)
{
    if (m_built) throw InvalidAppendAfterBuild();
    char* new_chars = new char[m_size + 1 + 1];
    if (m_size != 0)
    {
        std::strcpy(new_chars, m_chars);
        new_chars[m_size] = c;
        new_chars[m_size + 1] = '\0';
    }
    else
    {
        new_chars[0] = c;
        new_chars[1] = '\0';
    }
    if (m_chars) delete[] m_chars;
    m_chars = new_chars;
    m_size += 1;
}

void StringBuilder::append(const String& str)
{
    append(str.c_str());
}

void StringBuilder::prepend(const char * cstr)
{
    if (m_built) throw InvalidAppendAfterBuild();
    char* new_chars = new char[m_size + std::strlen(cstr) + 1];
    if (m_size != 0)
    {
        std::strcpy(new_chars, cstr);
        std::strcat(new_chars, m_chars);
    }
    else
    {
        std::strcpy(new_chars, cstr);
    }
    if (m_chars) delete[] m_chars;
    m_chars = new_chars;
    m_size = std::strlen(m_chars);
}

void StringBuilder::prepend(char c)
{
    if (m_built) throw InvalidAppendAfterBuild();
    char* new_chars = new char[m_size + 1 + 1];
    if (m_size != 0)
    {
        new_chars[0] = c;
        new_chars[1] = '\0';
        std::strcat(new_chars, m_chars);
    }
    else
    {
        new_chars[0] = c;
        new_chars[1] = '\0';
    }
    if (m_chars) delete[] m_chars;
    m_chars = new_chars;
    m_size += 1;
}

void StringBuilder::prepend(const String & str)
{
    prepend(str.c_str());
}

void StringBuilder::appendf(const char* fmt, ...)
{
    // FIXME: Unhandled possible failures (might return 0, etc).
    va_list args;
    va_start(args, fmt);
    unsigned size = std::vsnprintf (NULL, 0, fmt, args);
    va_end (args); 
    va_start(args, fmt);
    char* buf = new char[size + 1];
    std::vsnprintf (buf, size + 1, fmt, args);
    va_end (args);
    append (buf);
    delete[] buf;
}

void StringBuilder::prependf(const char* fmt, ...)
{
    // FIXME: Unhandled possible failures (might return 0, etc).
    va_list args;
    va_start(args, fmt);
    unsigned size = std::vsnprintf (NULL, 0, fmt, args);
    va_end (args); 
    va_start(args, fmt);
    char* buf = new char[size + 1];
    std::vsnprintf (buf, size + 1, fmt, args);
    va_end (args);
    prepend (buf);
    delete[] buf;
}

String StringBuilder::build()
{
    String s {};
    s.m_size = m_size;
    s.m_chars = m_chars;
    m_chars = nullptr;
    m_built = true;
    return s;
}

StringBuilder& StringBuilder::operator=(const StringBuilder& builder)
{
    if (m_chars) delete[] m_chars;
    m_chars = new char[builder.m_size + 1];
    std::strcpy(m_chars, builder.m_chars);
    m_size = builder.m_size;
    m_built = builder.m_built;
    return *this;
}

/*
StringBuilder& StringBuilder::operator+=(const char* cs)
{
    append(cs);
    return *this;
}

StringBuilder& StringBuilder::operator+=(const String& s)
{
    append(s.c_str());
    return *this;
}
*/


