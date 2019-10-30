#include "StringView.h"
#include "String.h"
#include <cstring>

StringView::StringView(const String& str)
    : m_chars(str.c_str()),
      m_size(str.size())
{}

StringView::StringView(const StringView& other)
    : m_chars(other.m_chars), 
      m_size(other.m_size)
{
}

StringView::StringView(const char* cstr) 
    : m_chars(cstr),
      m_size(strlen(cstr))
{}
