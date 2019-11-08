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

template<typename _T>
static inline constexpr _T min(_T&& left, _T&& right)
{
    return left < right ? left : right;
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
    constexpr StringView(const char* begin, const char* end);
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
    
    static constexpr bool equals_partially(const char* lhs, const char* rhs)
    {
        const std::size_t _size =  min(string_length(lhs), string_length(rhs));
        for (std::size_t i = 0; i < _size; ++i)
        {
            if (lhs[i] != rhs[i]) return false;
        }
        return true;
    }
    
    constexpr bool operator==(const char* other) const
    {
        if ((m_chars == nullptr && other != nullptr) ||
            (m_chars != nullptr && other == nullptr))
            return false;
        if (m_chars == nullptr && other == nullptr)
            return true;
        return m_chars == other || equals_partially(m_chars, other);
    }

    constexpr bool operator==(const StringView& other) const
    {
        if ((m_chars == nullptr && other.m_chars != nullptr) ||
            (m_chars != nullptr && other.m_chars == nullptr))
            return false;
        if (m_chars == nullptr && other.m_chars == nullptr)
            return true;
        return (m_chars == other.m_chars && m_size == other.m_size) ||
               equals_partially(m_chars, other.m_chars);
    }
    
    template<typename _StringType>
    constexpr bool operator==(const _StringType& other) const
    {
        if ((m_chars == nullptr && other.c_str() != nullptr) ||
            (m_chars != nullptr && other.c_str() == nullptr))
            return false;
        if (m_chars == nullptr && other.c_str() == nullptr)
            return true;
        return (m_chars == other.c_str() && m_size == other.size()) ||
               equals_partially(m_chars, other.c_str());
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

constexpr StringView::StringView(const char *begin, const char *end)
    : m_chars(begin), m_size(end-begin)
{
}

constexpr StringView operator""_sv(const char* cstr, unsigned long size)
{
    return StringView(cstr, size);
}

#endif // STRINGVIEW_H
