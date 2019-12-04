#include "StringView.h"
#include "String.h"
#include <cstring>

StringView::StringView(const String& str) : m_chars(str.c_str()), m_size(str.size())
{
}
