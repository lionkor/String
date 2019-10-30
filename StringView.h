#ifndef STRINGVIEW_H
#define STRINGVIEW_H

#include <ostream>
using size_t = unsigned long;

/// View to a null-terminated string.
class StringView
{
public:
    StringView(const char*);
    StringView(const class String&);
    StringView(const StringView&);

    inline constexpr bool is_valid() const { return m_chars != nullptr; }
    inline constexpr bool is_empty() const { return m_size == 0 || m_chars[0] == 0; }
    inline constexpr size_t size() const { return m_size; }
    inline constexpr const char* chars() const { return m_chars; }

    friend std::ostream& operator<<(std::ostream& os, const StringView& view)
    {
        return os << view.m_chars;
    }

private:
    const char* m_chars;
    size_t m_size;
};

#endif // STRINGVIEW_H
