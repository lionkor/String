#ifndef STRINGVIEW_H
#define STRINGVIEW_H

#include <ostream>
#include <cstring>

using size_t = unsigned long;

/// View to a null-terminated string.
class StringView
{
public:
    StringView();
    StringView(const char*);
    StringView(const class String&);
    StringView(const StringView&);

    inline constexpr bool is_valid() const { return m_chars != nullptr; }
    inline constexpr bool is_empty() const { return m_size == 0 || m_chars[0] == 0; }
    inline constexpr size_t size() const { return m_size; }
    inline constexpr const char* chars() const { return m_chars; }
    inline constexpr const char* c_str() const { return m_chars; }

    bool operator==(const char* other) const;
    bool operator==(const StringView& other) const;
    
    bool operator!=(const char* other) const;
    bool operator!=(const StringView& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const StringView& view)
    {
        if (view.m_chars)       
            return os << view.m_chars;
        else
            return os << "";
    }

private:
    const char* m_chars;
    size_t m_size;
};

#endif // STRINGVIEW_H
