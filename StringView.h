#ifndef STRINGVIEW_H
#define STRINGVIEW_H

#include <cassert>
#include <cstring>
#include <ostream>

using size_t = unsigned long;

static inline constexpr std::size_t string_length(const char* cstr)
{
    assert(cstr != nullptr);
    std::size_t length = 0;
    while (*cstr != '\0')
    {
        length++;
        cstr++;
    }
    return length;
}

/// View to a null-terminated string.
class StringView
{
public:
    constexpr StringView() : m_chars(nullptr), m_size(0) {}
    constexpr StringView(const char* cstr) : m_chars(cstr), m_size(string_length(cstr)) {}
    constexpr StringView(const char* cs, std::size_t sz) : m_chars(cs), m_size(sz) {}
    constexpr StringView(const StringView& other)
        : m_chars(other.m_chars), m_size(other.m_size)
    {
    }
    StringView(const class String&);

    inline constexpr bool is_valid() const { return m_chars != nullptr; }
    inline constexpr bool is_empty() const { return m_size == 0 || m_chars[0] == 0; }
    inline constexpr size_t size() const { return m_size; }
    inline constexpr const char* chars() const { return m_chars; }
    inline constexpr const char* c_str() const { return m_chars; }

    constexpr const char& operator[](std::size_t i) const
    {
        return m_chars[i];
    }
    
    constexpr bool operator==(const char* other) const
    {
        if ((m_chars == nullptr && other != nullptr) ||
            (m_chars != nullptr && other == nullptr))
            return false;
        if (m_chars == nullptr && other == nullptr)
            return true;
        return m_chars == other || !std::strcmp(m_chars, other);
    }

    constexpr bool operator==(const StringView& other) const
    {
        if ((m_chars == nullptr && other.m_chars != nullptr) ||
            (m_chars != nullptr && other.m_chars == nullptr))
            return false;
        if (m_chars == nullptr && other.m_chars == nullptr)
            return true;
        return (m_chars == other.m_chars && m_size == other.m_size) ||
               !std::strcmp(m_chars, other.m_chars);
    }

    constexpr bool operator!=(const char* other) const { return !(m_chars == other); }

    constexpr bool operator!=(const StringView& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& os, const StringView& view)
    {
        if (view.m_chars)
            return os << view.m_chars;
        else
            return os << "";
    }

private:
    const char* m_chars;
    const size_t m_size;
};

constexpr StringView operator""_sv(const char* cstr, unsigned long size)
{
    return StringView(cstr, size);
}

#endif // STRINGVIEW_H
