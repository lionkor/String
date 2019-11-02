#include "StringView.h"
#include "String.h"
#include <cstring>

StringView::StringView(const String& str) : m_chars(str.c_str()), m_size(str.size()) {}

StringView::StringView(const StringView& other)
    : m_chars(other.m_chars), m_size(other.m_size)
{
}

// "the empty string view"
StringView::StringView() : m_chars(nullptr), m_size(0) {}

StringView::StringView(const char* cstr) : m_chars(cstr), m_size(std::strlen(cstr)) {}

bool StringView::operator==(const char* other) const
{
    if ((m_chars == nullptr && other != nullptr) ||
        (m_chars != nullptr && other == nullptr))
        return false;
    if (m_chars == nullptr && other == nullptr)
        return true;
    return m_chars == other || !std::strcmp(m_chars, other);
}

bool StringView::operator==(const StringView& other) const
{
    if ((m_chars == nullptr && other.m_chars != nullptr) ||
        (m_chars != nullptr && other.m_chars == nullptr))
        return false;
    if (m_chars == nullptr && other.m_chars == nullptr)
        return true;
    return (m_chars == other.m_chars && m_size == other.m_size) ||
           !std::strcmp(m_chars, other.m_chars);
}

bool StringView::operator!=(const char* other) const { return !(m_chars == other); }

bool StringView::operator!=(const StringView& other) const { return !(*this == other); }
