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
    // CAUTION: Do *not* rely on the iterators being aliases for
    // std::vector iterators. This might change at any point. 
    using Iterator             = std::vector<char>::iterator;
    using ConstIterator        = std::vector<char>::const_iterator;
    using ReverseIterator      = std::vector<char>::reverse_iterator;
    using ConstReverseIterator = std::vector<char>::const_reverse_iterator;

    /// New empty string, equivalent to String("")(
    String();
    /// New string with cstr as content
    String(const char* cstr);
    /// New string from another string's iterators.
    String(ConstIterator from, ConstIterator to);

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
    /// Size or length of the string.
    std::size_t size() const;
    /// Length or size of the string.
    std::size_t length() const;

    /// A unique_ptr managed char[] containing a copy of the data of the string,
    /// guaranteed to be null-terminated.
    std::unique_ptr<char> as_c_string() const;
    /// A copy of this string represented as a std::string.
    std::string as_std_string() const;

    /// Clears the contents of the string, resulting string will be the empty string.
    void clear();

    /// Inserts a char before the position pointed to by the iterator. May invalidate
    /// iterators.
    void insert(ConstIterator iter, char c);
    /// Inserts the string before the position pointed to by the iterator. May invalidate
    /// iterators.
    void insert(ConstIterator iter, const String& s);
    /// Inserts the part of the string specified by the begin and end iterators
    /// before the position pointed to by the "iter" iterator. May invalidate iterators.
    void insert(ConstIterator iter, ConstIterator begin, ConstIterator end);

    /// Removes the element pointed to by the iterator. Invalidates iterators.
    void erase(ConstIterator iter);
    /// Removes elements between from and to. Invalidates iterators.
    void erase_from_to(ConstIterator from, ConstIterator to);
    /// Removes n elements starting at the iterator position. Invalidates iterators.
    void erase_n(ConstIterator iter, std::size_t n);

    /// A copy of the chars between from and to, as a new string.
    String substring(ConstIterator from, ConstIterator to) const;
    /// A copy of the first n chars from start, as a new string.
    String substring(ConstIterator start, std::size_t n) const;
};

#endif // STRING_H
