#include "String.h"
#include "Exceptions.h"
#include "StringBuilder.h"// FIXME: Remove.

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
    /* NOTE:
     * This sucks. It should not use varargs.
     * Format Strings are a bad idea.
     * I know this, and I am working on a better way to do this.
     * See FIXME below.
     */
    
    // FIXME: Rewrite this to use variadic templates.
    String s {};
    va_list args;
    va_start(args, fmt);
    int size = std::vsnprintf (NULL, 0, fmt, args);
    
    // vsnprintf returns <0 if encoding error occured.
    if (size < 0) throw FormatEncodingError();
    
    va_end (args);
    s.m_chars = std::make_unique<char[]>(size+1);
    va_start(args, fmt);
    int rc = std::vsnprintf (s.m_chars.get(), size + 1, fmt, args);
    
    // vsnprintf returns <0 if encoding error occured.
    if (rc < 0) throw FormatEncodingError();
    
    // vsnprintf returns >0 and <n on success. 
    // This is sadly a super generic error.
    if (rc >= size+1) throw FormatWriteFault(); 
    
    va_end (args);
    s.m_size = size;
    return s;
}

std::vector<String> String::split(char delim) const
{
    // TODO/FIXME: if (str.find(delim) == std::string::npos) return std::vector<std::string>();
    std::vector<String> splits {};
    std::size_t pos { 0 };
    for (const char* c = m_chars.get(); true; ++c)
    {
        if (*c == delim || *c == '\0') 
        {
            splits.push_back(substr(pos, (c - m_chars.get()) - pos));
            if (*c == '\0') break;
            pos = ++c - m_chars.get();
        }
    }
    return splits;
}

String String::substr(std::size_t pos, std::size_t n) const
{
    String s;
    s.m_chars = std::make_unique<char[]>(n+1);
    for (std::size_t i = 0; i < n; ++i)
    {
        s.m_chars[i] = m_chars[pos+i];
    }
    s.m_chars[n] = '\0';
    s.m_size = n;
    return s;
}

String String::trim(char trim) const
{
    const char* begin = m_chars.get();
    const char* end = m_chars.get() + m_size - 1;
    while(*begin == trim) ++begin;
    while(*end == trim) --end;
    return substr(begin-m_chars.get(), end+1-begin);
}

