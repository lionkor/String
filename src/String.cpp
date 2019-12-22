#include "String.h"
#include "Exceptions.h"
#include "StringBuilder.h" // FIXME: Remove.
#include <cassert>
#include <cmath>

// "the empty string"
String::String()
{
    m_chars.all.dynamic = false;
    set_size(0);
    chars()[0] = '\0';
}


String::String(const char* cs)
{
    store(cs);
}

template<typename _T>
static constexpr std::size_t abs_size_t(_T i)
{
    return std::size_t(i < 0 ? i * -1 : i);
}

String::String(const String::Iterator start, const String::Iterator end)
{
    store(start, abs_size_t(end - start));
    // FIXME: Doesn't work if start>end.
}

String::String(const String& str)
{
    store(str.chars(), str.size());
}

String::String(const StringView& sv)
{
    store(sv.chars(), sv.size());
}

String& String::operator=(const String& str)
{
    const auto tmp_size = str.size();
    if (str.m_chars.all.dynamic)
    {
        m_chars.all.dynamic = true;
        set_size(tmp_size);
        m_chars.heap.data = new char[size() + 1];
        set_size(str.size());
    }
    else
    {
        m_chars.all.dynamic = false;
        set_size(str.size());
    }
    std::strcpy(chars(), str.chars());
    return *this;
}

String& String::operator=(const char* cs)
{
    const auto tmp_size = std::strlen(cs);
    if (size() > MAX_ALLOC)
    {
        m_chars.all.dynamic = true;
        set_size(tmp_size);
        m_chars.heap.data = new char[size() + 1];
    }
    else
    {
        m_chars.all.dynamic = false;
        set_size(tmp_size);
    }
    std::strcpy(chars(), cs);
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

String::~String()
{
    if (m_chars.all.dynamic)
        delete[] chars();
}

std::vector<String> String::split(char delim) const
{
    // TODO/FIXME: if (str.find(delim) == std::string::npos) return
    // std::vector<std::string>();
    std::vector<String> splits {};
    std::size_t         pos { 0 };
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

bool String::equals(const String& str) const
{
    return *this == str;
}


String String::substring(std::size_t pos, std::size_t n) const
{
    String s;
    if (n > MAX_ALLOC)
    {
        s.m_chars.all.dynamic = true;
        s.m_chars.heap.data   = new char[n + 1];
        s.chars()[n]          = '\0';
    }
    else
    {
        s.m_chars.all.dynamic = false;
        s.chars()[n]          = '\0';
    }
    s.set_size(n);
    std::strncpy(s.chars(), chars() + pos, n);
    return s;
}


String String::substring(const Iterator begin, const Iterator end) const
{
    String     s;
    const auto tmp_size = end - begin;
    if (tmp_size > MAX_ALLOC)
    {
        s.m_chars.all.dynamic = true;
        s.set_size(tmp_size);
        s.m_chars.heap.data = new char[s.size() + 1];
        s.chars()[s.size()] = '\0';
    }
    else
    {
        s.m_chars.all.dynamic = false;
        s.set_size(tmp_size);
        s.chars()[s.size()] = '\0';
    }
    std::strncpy(s.chars(), begin, s.size());
    return s;
}


String String::substr(std::size_t pos, std::size_t n) const
{
    return substring(pos, n);
}
String String::substr(const Iterator begin, const Iterator end) const
{
    return substring(begin, end);
}

String String::trimmed(char trim) const
{
    Iterator begin = chars();
    Iterator end   = chars() + size();
    while (*begin == trim)
        ++begin;
    while (*(end - 1) == trim && end > begin)
        --end;
    return substring(begin, end);
}

String String::hexified() const
{
    StringBuilder sb;
    for (const char& c : *this)
    {
        sb.append(HexFormat<unsigned>(c));
    }
    return sb.build();
}

String String::capitalized() const
{
    return String::format(char(toupper(chars()[0])), substring(begin() + 1, end()));
}

String String::replaced(const StringView& to_replace,
                        const StringView& replace_with) const
{
    if (to_replace == replace_with)
        return String(*this);
    StringBuilder sb;
    for (std::size_t i = 0; i < size(); ++i)
    {
        if (chars()[i] == to_replace[0])
        {
            if (substring(i, to_replace.size()) == to_replace)
            {
                sb.append(replace_with);
                i += to_replace.size() - 1;
                continue;
            }
        }
        else
        {
            sb.append(chars()[i]);
        }
    }
    return sb.build();
}

String String::replaced(char to_replace, char replace_with) const
{
    if (to_replace == replace_with)
        return String(*this);
    StringBuilder sb;
    for (const char& c : *this)
    {
        if (c == to_replace)
            sb.append(replace_with);
        else
            sb.append(c);
    }
    return sb.build();
}

String String::to_upper() const
{
    StringBuilder sb;
    for (const char& c : *this)
    {
        sb.append(char(toupper(c)));
    }
    return sb.build();
}

String String::to_lower() const
{
    StringBuilder sb;
    for (const char& c : *this)
    {
        sb.append(char(tolower(c)));
    }
    return sb.build();
}

String String::to_printable_only() const
{
    StringBuilder sb;
    for (const char& c : *this)
    {
        if (isprint(c))
        {
            sb.append(c);
        }
    }
    return sb.build();
}

String::Iterator String::find(const char c) const
{
    Iterator current = begin();
    for (; *current != c && current != end(); ++current)
        ;
    return current;
}

const char* String::c_str() const
{
    return m_chars.all.dynamic ? m_chars.heap.data : m_chars.stack.data;
}

bool String::equals_case_insensitive(const String& str) const
{
    if (size() != str.size())
        return false;
    for (std::size_t i = 0; i < str.size(); ++i)
    {
        if (!char_equals_case_insensitive(chars()[i], str[i]))
            return false;
    }
    return true;
}

bool String::endswith(const String& str) const
{
    for (std::size_t i = 0; i < str.size(); ++i)
    {
        if (chars()[size() - 1 - i] != str[str.size() - 1 - i])
            return false;
    }
    return true;
}

bool String::startswith(const String& str) const
{
    return substring_view(0, str.size()) == str;
}

StringView String::substring_view(const std::size_t position, const std::size_t n) const
{
    const Iterator start(m_chars.all.dynamic ? m_chars.heap.data + position
                                             : m_chars.stack.data + position);
    return StringView(start, start + n);
}

bool String::contains(char c) const
{
    return find(c) != end();
}
