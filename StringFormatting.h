#ifndef STRINGFORMATTING_H
#define STRINGFORMATTING_H

#include "String.h"

template<typename... _Args>
[[nodiscard]] String String::format(StringBuilder& sb)
{
    return sb.build();
}

template<typename _T, typename... _Args>
String String::format(StringBuilder&& sb, _T&& t)
{
    sb.append(t);
    return String::format(sb);
}

template<typename _T, typename... _Args>
String String::format(StringBuilder&& sb, _T&& t, _Args&&... args)
{
    sb.append(t);
    return String::format(std::move(sb), args...);
}

template<typename... _Args>
String String::format(_Args&&... args)
{
    StringBuilder sb;
    return format(std::move(sb), args...);
}

#endif // STRINGFORMATTING_H
