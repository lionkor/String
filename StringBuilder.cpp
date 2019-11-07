#include "StringBuilder.h"
#include "Exceptions.h"
#include "String.h"
#include <cctype>
#include <cstdlib>

//#define DEBUG_STRING_BUILDER

#ifdef DEBUG_STRING_BUILDER
#define log_strbuild(x)                                                                  \
    std::cout << "[DEBUG] StringBuilder:" << __LINE__ << ": " << x << std::endl
#else
#define log_strbuild(x)
#endif

StringBuilder::StringBuilder()
{
    m_chars = new char[16] { 0 };
    m_size = 0;
    m_capacity = 16;
}

StringBuilder::StringBuilder(StringBuilder&& sb)
{
    m_chars = std::move(sb.m_chars);
    m_built = std::move(sb.m_built);
    m_size = std::move(sb.m_size);
}

StringBuilder::~StringBuilder() { delete[] m_chars; }

StringBuilder& StringBuilder::append(const char* cstr)
{
    log_strbuild(__PRETTY_FUNCTION__ << " with cstr = _" << cstr << "_");
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    _print_memory(cstr, strlen(cstr), "StringBuilder::append arg");

    concat(m_chars, cstr);
    return *this;
}

StringBuilder& StringBuilder::append(int i)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%i", i);
    concat(m_chars, tmp);
    return *this;
}

StringBuilder& StringBuilder::append(short arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%i", arg);
    return append(tmp);
}

StringBuilder& StringBuilder::append(unsigned short arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%u", arg);
    return append(tmp);
}

StringBuilder& StringBuilder::append(long arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%li", arg);
    return append(tmp);
}

StringBuilder& StringBuilder::append(unsigned arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%u", arg);
    return append(tmp);
}

StringBuilder& StringBuilder::append(unsigned long arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%lu", arg);
    return append(tmp);
}

StringBuilder& StringBuilder::append(unsigned long long arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%llu", arg);
    return append(tmp);
}

StringBuilder& StringBuilder::append(unsigned char arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%u", arg);
    return append(tmp);
}

StringBuilder& StringBuilder::append(float arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%f", double(arg)); // FIXME: double!?
    return append(tmp);
}

StringBuilder& StringBuilder::append(double arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%f", arg);
    return append(tmp);
}

StringBuilder& StringBuilder::append(long double arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%LG", arg);
    return append(tmp);
}

StringBuilder& StringBuilder::append(char c)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[1] { c };
    concat(m_chars, tmp);
    return *this;
}

StringBuilder& StringBuilder::append(const String& str) { return append(str.chars()); }

StringBuilder& StringBuilder::prepend(const char* cstr)
{
    log_strbuild(__PRETTY_FUNCTION__ << " with cstr = _" << cstr << "_");
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    _print_memory(cstr, strlen(cstr), "StringBuilder::prepend arg");

    concat(m_chars, cstr);
    return *this;
}

StringBuilder& StringBuilder::prepend(int i)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%i", i);
    concat(m_chars, tmp);
    return *this;
}

StringBuilder& StringBuilder::prepend(short arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%i", arg);
    return prepend(tmp);
}

StringBuilder& StringBuilder::prepend(unsigned short arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%u", arg);
    return prepend(tmp);
}

StringBuilder& StringBuilder::prepend(long arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%li", arg);
    return prepend(tmp);
}

StringBuilder& StringBuilder::prepend(unsigned arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%u", arg);
    return prepend(tmp);
}

StringBuilder& StringBuilder::prepend(unsigned long arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%lu", arg);
    return prepend(tmp);
}

StringBuilder& StringBuilder::prepend(unsigned long long arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%llu", arg);
    return prepend(tmp);
}

StringBuilder& StringBuilder::prepend(unsigned char arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%u", arg);
    return prepend(tmp);
}

StringBuilder& StringBuilder::prepend(float arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%f", double(arg)); // FIXME: double!?
    return prepend(tmp);
}

StringBuilder& StringBuilder::prepend(double arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%f", arg);
    return prepend(tmp);
}

StringBuilder& StringBuilder::prepend(long double arg)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[16] { 0 };
    sprintf(tmp, "%LG", arg);
    return prepend(tmp);
}

StringBuilder& StringBuilder::prepend(char c)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();

    char tmp[1] { c };
    concat(m_chars, tmp);
    return *this;
}

StringBuilder& StringBuilder::prepend(const String& str) { return prepend(str.chars()); }

String StringBuilder::build()
{
    if (m_built)
        throw StringBuilder_DoubleBuildNotAllowed();
    String s(std::move(m_chars));
    m_built = true;
    return s;
}

StringBuilder& StringBuilder::operator=(StringBuilder&& sb)
{
    m_chars = std::move(sb.m_chars);
    m_built = std::move(sb.m_built);
    m_size = std::move(sb.m_size);
    return *this;
}
