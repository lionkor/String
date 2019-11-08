#ifndef STRING_H
#define STRING_H

#include <cstdarg>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "Core.h"
#include "StringBuilder.h"
#include "StringView.h"

static constexpr unsigned char MAX_ALLOC = 23;

static constexpr char to_lower_internal(const char c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

static constexpr bool char_equals_case_insensitive(char lhs, char rhs)
{
    return to_lower_internal(lhs) == to_lower_internal(rhs);
}

class String
{
public:
    friend class StringBuilder;
    using Iterator = const char*;

    String();
    String(const char*);
    String(const Iterator start, const Iterator end);
    String(const String&);
    String(const StringView&);

    ~String();

    String& operator=(const String&);
    String& operator=(const char*);

    bool operator==(const String&) const;
    bool operator==(const char*) const;

    inline bool operator!=(const String& other) const { return !(*this == other); }
    inline bool operator!=(const char* other) const { return !(*this == other); }

    inline char operator[](const std::size_t index) const { return chars()[index]; }

    constexpr Iterator begin() const
    {
        return m_chars.all.dynamic ? &m_chars.heap.data[0] : &m_chars.stack.data[0];
    }
    
    constexpr Iterator end() const
    {
        return m_chars.all.dynamic ? &m_chars.heap.data[m_chars.heap.size]
                                   : &m_chars.stack.data[m_chars.stack.size];
    }

    String substring(std::size_t position, std::size_t n) const;
    String substring(const Iterator begin, const Iterator end) const;
    String trimmed(char trimmed = ' ') const;
    String hexified() const;
    String capitalized() const;
    String replaced(const StringView& to_replace, const StringView& replace_with) const;
    String replaced(char to_replace, char replace_with) const;
    String to_upper() const;
    String to_lower() const;
    String to_printable_only() const;
    constexpr StringView substring_view(const std::size_t position, const std::size_t n) const;
    
    Iterator find(const char c) const;
    std::vector<String> split(char delim) const;

    inline StringView as_string_view() const { return StringView(*this); }
    inline bool empty() const { return size() == 0; }
    
    constexpr bool startswith(const String& str) const;
    constexpr bool endswith(const String& str) const;
    constexpr bool equals(const String& str) const;
    constexpr bool equals_case_insensitive(const String& str) const;

    const char* c_str() const;

    [[deprecated("use substring instead")]] String substr(std::size_t pos,
                                                          std::size_t n) const;

    [[deprecated("use substring instead")]] String substr(const Iterator begin,
                                                          const Iterator end) const;

    friend std::ostream& operator<<(std::ostream& os, const String& str)
    {
        return os << str.chars();
    }

    template<typename... _Args>
    [[nodiscard]] static String format(StringBuilder& sb)
    {
        return sb.build();
    }

    template<typename _T, typename... _Args>
    static String format(StringBuilder&& sb, _T&& t)
    {
        sb.append(t);
        return String::format(sb);
    }

    template<typename _T, typename... _Args>
    static String format(StringBuilder&& sb, _T&& t, _Args&&... args)
    {
        sb.append(t);
        return String::format(std::move(sb), args...);
    }

    template<typename... _Args>
    static String format(_Args&&... args)
    {
        StringBuilder sb;
        return format(std::move(sb), args...);
    }

    inline std::size_t size() const
    {
        return m_chars.all.dynamic ? m_chars.heap.size : m_chars.stack.size;
    }

protected:
    inline void set_size(std::size_t size)
    {
        if (m_chars.all.dynamic)
            m_chars.heap.size = size;
        else
            m_chars.stack.size = size;
    }

    inline const char* chars() const
    {
        return m_chars.all.dynamic ? m_chars.heap.data : m_chars.stack.data;
    }

    inline char* chars()
    {
        return m_chars.all.dynamic ? m_chars.heap.data : m_chars.stack.data;
    }

    inline void store(const char* cstr, const std::size_t csize)
    {
        if (csize > MAX_ALLOC)
        {
            m_chars.all.dynamic = true;
            set_size(csize);
            m_chars.heap.data = new char[size() + 1];
        }
        else
        {
            m_chars.all.dynamic = false;
            set_size(csize);
        }

        if (chars() != cstr && cstr != nullptr && chars() != nullptr)
            strcpy(chars(), cstr);
    }

    inline void store(const char* cstr) { store(cstr, strlen(cstr)); }

    inline void resize(int delta)
    {
        // FIXME: This is very inefficient. We should implement capacity in m_chars.heap
        if (m_chars.all.dynamic)
        {
            char* new_chars = new char[m_chars.heap.size + 1];
            std::memcpy(new_chars, m_chars.heap.data, m_chars.heap.size);
            delete[] m_chars.heap.data;
            m_chars.heap.data = new_chars;
            m_chars.heap.size += delta;
        }
        else
        {
            std::memset(m_chars.stack.data + m_chars.stack.size, 0, delta);
            m_chars.stack.size += delta;
        }
    }

    inline void set_dynamic(bool dynamic) { m_chars.all.dynamic = dynamic; }

    union MainDataUnion {
        MainDataUnion() {}
        struct
        {
            unsigned char dynamic : 1;
        } all;
        struct
        {
            unsigned char dynamic : 1 = 1;
            std::size_t size : std::numeric_limits<std::size_t>::digits - 1;
            // FIXME: Implement capacity
            char* data;
        } heap;
        struct
        {
            unsigned char dynamic : 1 = 0;
            unsigned char size : std::numeric_limits<unsigned char>::digits - 1;
            char data[MAX_ALLOC];
        } stack;
    } m_chars;
};

constexpr StringView String::substring_view(const std::size_t position, const std::size_t n) const
{
    const Iterator start(m_chars.all.dynamic ? m_chars.heap.data + position 
                                             : m_chars.stack.data + position);
    return StringView(start, start + n);
}

constexpr bool String::startswith(const String& str) const
{
    return substring_view(0, str.size()) == str;
}

constexpr bool String::endswith(const String &str) const
{
    for (std::size_t i = 0; i < str.size(); ++i)
    {
        if (chars()[size() - 1 - i] != str[str.size() - 1 - i])
            return false;
    }
    return true;
}

constexpr bool String::equals(const String &str) const
{
    return *this == str;
}

constexpr bool String::equals_case_insensitive(const String &str) const
{
    if (size() != str.size()) return false;
    for (std::size_t i = 0; i < str.size(); ++i)
    {
        if (!char_equals_case_insensitive(chars()[i], str[i]))
            return false;
    }
    return true;
}


#include "StringFormatting.h"

#endif // STRING_H
