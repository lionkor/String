#include "String.h"
#include "Exceptions.h"
//#include "StringBuilder.h" // FIXME: Remove.
#include <cassert>
#include <cmath>

// "the empty string"
String::String()
{
    set_size(0);
    m_chars.all.dynamic = false;
    m_chars.stack.data[0] = '\0';
}


String::String(const char* cs) 
{
    set_size(std::strlen(cs));
    if (size() > MAX_ALLOC)
    {
        m_chars.all.dynamic = true;
        m_chars.heap.data = new char[size() + 1];
        std::strcpy(m_chars.heap.data, cs);
    }
    else
    {
        m_chars.all.dynamic = false;
        std::strcpy(m_chars.stack.data, cs);
    }
}

template<typename _T>
static constexpr std::size_t abs_size_t(_T i)
{
    return std::size_t(i < 0 ? i * -1 : i);
}

String::String(const String::Iterator start, const String::Iterator end)
{
    set_size(abs_size_t(end - start));
    if (size() > MAX_ALLOC)
    {
        m_chars.all.dynamic = true;
        m_chars.heap.data = new char[size() + 1];
        std::strncpy(m_chars.heap.data, start, size());
    }
    else
    {
        m_chars.all.dynamic = false;
        std::strncpy(m_chars.stack.data, start, size());
    }
    // FIXME: Doesn't work if start>end.
}

String::String(const String& str)
{
    set_size(str.size());
    if (str.m_chars.all.dynamic)
    {
        m_chars.all.dynamic = true;
        m_chars.heap.data = new char[size() + 1];
    }
    else
    {
        m_chars.all.dynamic = false;
        std::strcpy(m_chars.stack.data, str.chars());
    }
}

String::~String()
{
    if (m_chars.all.dynamic)
        delete[] m_chars.heap.data;
}

String& String::operator=(const String& str)
{
    set_size(str.size());
    if (str.m_chars.all.dynamic)
    {
        m_chars.all.dynamic = true;
        m_chars.heap.data = new char[size() + 1];
        std::strcpy(m_chars.heap.data, str.chars());
    }
    else
    {
        m_chars.all.dynamic = false;
        std::strcpy(m_chars.stack.data, str.chars());
    }
    return *this;
}

String& String::operator=(const char* cs)
{
    set_size(std::strlen(cs));
    if (size() > MAX_ALLOC)
    {
        m_chars.all.dynamic = true;
        m_chars.heap.data = new char[size() + 1];
        std::strcpy(m_chars.heap.data, cs);
    }
    else
    {
        m_chars.all.dynamic = false;
        std::strcpy(m_chars.stack.data, cs);
    }
    return *this;
}

bool String::operator==(const String& other) const
{
    return std::strcmp(chars(), other.chars()) == 0;
}

bool String::operator==(const char* other) const
{
    return std::strcmp(chars(), other) == 0;
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
    int size = std::vsnprintf(nullptr, 0, fmt, args);

    // vsnprintf returns <0 if encoding error occured.
    if (size < 0)
        throw FormatEncodingError();
    s.set_size(unsigned(size));

    va_end(args);
    int rc;
    if (s.size() > MAX_ALLOC)
    {
        s.m_chars.all.dynamic = true;
        s.m_chars.heap.data = new char[s.size() + 1];
        rc = std::vsnprintf(s.m_chars.heap.data, s.size() + 1, fmt, args);
    }
    else
    {
        s.m_chars.all.dynamic = false;
        rc = std::vsnprintf(s.m_chars.stack.data, s.size() + 1, fmt, args);
    }
    va_start(args, fmt);

    // vsnprintf returns <0 if encoding error occured.
    if (rc < 0)
        throw FormatEncodingError();

    // vsnprintf returns >0 and <n on success.
    // This is sadly a super generic error.
    if (rc >= s.size() + 1)
        throw FormatWriteFault();

    va_end(args);

    return s;
}

std::vector<String> String::split(char delim) const
{
    // TODO/FIXME: if (str.find(delim) == std::string::npos) return
    // std::vector<std::string>();
    std::vector<String> splits {};
    std::size_t pos { 0 };
    for (const char* c = chars(); true; ++c)
    {
        if (*c == delim || *c == '\0')
        {
            splits.push_back(substring(pos, (c - chars()) - pos));
            if (*c == '\0')
                break;
            pos = ++c - chars();
        }
    }
    return splits;
}

String::Iterator String::begin() const { return &chars()[0]; }

String::Iterator String::end() const { return &chars()[size()]; }


String String::substring(std::size_t pos, std::size_t n) const
{
    String s;
    if (n > MAX_ALLOC)
    {
        s.m_chars.all.dynamic = true;
        s.m_chars.heap.data = new char[n + 1];
        std::strncpy(s.m_chars.heap.data, chars() + pos, n);
        s.m_chars.heap.data[n] = '\0';
    }
    else
    {
        s.m_chars.all.dynamic = false;
        std::strncpy(s.m_chars.stack.data, chars() + pos, n);
        s.m_chars.stack.data[n] = '\0';
    }
    s.set_size(n);
    return s;
}


String String::substring(const Iterator begin, const Iterator end) const
{
    String s;
    s.set_size(end - begin);
    if (s.size() > MAX_ALLOC)
    {
        s.m_chars.all.dynamic = true;
        s.m_chars.heap.data = new char[s.size() + 1];
        std::strncpy(s.m_chars.heap.data, begin, s.size());
        s.m_chars.heap.data[s.size()] = '\0';
    }
    else
    {
        s.m_chars.all.dynamic = false;
        std::strncpy(s.m_chars.stack.data, begin, s.size());
        s.m_chars.stack.data[s.size()] = '\0';
    }
    return s;
}

String String::substr(std::size_t pos, std::size_t n) const { return substring(pos, n); }
String String::substr(const Iterator begin, const Iterator end) const
{
    return substring(begin, end);
}

String String::trim(char trim) const
{
    Iterator begin = chars();
    Iterator end = chars() + size();
    while (*begin == trim)
        ++begin;
    while (*(end - 1) == trim && end > begin)
        --end;
    return substring(begin, end);
}
