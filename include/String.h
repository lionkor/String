#ifndef STRING_H
#define STRING_H

#include <cstdarg>
#include <iostream>
#include <memory>
#include <vector>

/// \brief The String class represents a not-null-terminated string.
///
/// Implemented as a wrapper around a std::vector<char> for safety, simplicity and speed.
/// It is *not* null-terminated. If a null-terminated string is needed, it's very simple
/// to convert to a std::string or c-string.
class String
{
private:
    std::vector<char> m_chars;

public:
    using Iterator             = std::vector<char>::iterator;
    using ConstIterator        = std::vector<char>::const_iterator;
    using ReverseIterator      = std::vector<char>::reverse_iterator;
    using ConstReverseIterator = std::vector<char>::const_reverse_iterator;

    /// New empty string, equivalent to String("")(
    String();
    /// New string with cstr as content
    String(const char* cstr);

    String(const String&) = default;
    String(String&&)      = default;
    String& operator=(const String&) = default;

    /// Begin iterator. Points to the first char in the string.
    Iterator begin();
    /// Const begin iterator. Points to the first char in the string.
    ConstIterator begin() const;
    /// End iterator. points at the position past the end of the string.
    Iterator end();
    /// Const end iterator. points at the position past the end of the string.
    ConstIterator end() const;
    /// Accesses the char at position i in the string.
    char& at(std::size_t i);
    /// Accesses the char at position i in the string.
    char at(std::size_t i) const;
    /// True if the string is empty, i.e. has length 0
    bool empty() const;
    /// Size / length of the string.
    std::size_t size() const;
    std::size_t length() const;

    std::unique_ptr<char> as_c_string() const;
    std::string           as_std_string() const;

    void clear();
    void insert(ConstIterator iter, char c);
    void insert(ConstIterator iter, const String& s);
    void insert(ConstIterator iter, ConstIterator begin, ConstIterator end);

    void erase(ConstIterator iter);
    void erase_from_to(ConstIterator from, ConstIterator to);
    void erase_n(ConstIterator iter, std::size_t n);
};

#endif // STRING_H
