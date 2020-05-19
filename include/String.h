#ifndef STRING_H
#define STRING_H

#include <cstdarg>
#include <iostream>
#include <memory>
#include <vector>

/// \brief The String class represents a not-null-terminated string.
/// \author `lionkor` (Lion Kortlepel)
///
/// A String class without many of the inconsistencies that `std::string` brings, and many helper
/// functions, making it more alike Python or .NET strings.
///
/// Implemented as a wrapper around a `std::vector<char>` for safety, simplicity and speed.
/// This means that any `<algorithm>` calls should work as expected.
///
/// \attention String is \b not null-terminated. If a null-terminated string is needed, it's very simple
/// to convert to a `std::string` or c-string via `String::as_c_string` and `String::as_std_string`.
class String
{
private:
    std::vector<char> m_chars;

public:
    /// \brief Iterators used to iterate over the String.
    /// \attention Do *not* rely on these iterators being aliases for
    /// std::vector iterators. This might change at any point. Treat them as
    /// their own types.
    using Iterator             = std::vector<char>::iterator;
    using ConstIterator        = std::vector<char>::const_iterator;
    using ReverseIterator      = std::vector<char>::reverse_iterator;
    using ConstReverseIterator = std::vector<char>::const_reverse_iterator;

    /// \brief New empty string, equivalent to `""`
    String();
    /// \brief New string with only the char `c`.
    explicit String(char c);
    /// \brief New string with cstr as content
    String(const char* cstr);
    /// \brief New string from another string's iterators.
    String(ConstIterator from, ConstIterator to);

    String(const String&) = default;
    String(String&&)      = default;
    String& operator=(const String&) = default;

    /// \brief Begin iterator. Points to the first char in the string.
    Iterator begin();
    /// \brief Const begin iterator. Points to the first char in the string.
    ConstIterator begin() const;
    /// \brief End iterator. points at the position past the end of the string.
    Iterator end();
    /// \brief Const end iterator. points at the position past the end of the string.
    ConstIterator end() const;
    /// \brief Accesses the character at position `i` in the string.
    /// \throw std::out_of_range if `i` is an invalid index
    char& at(std::size_t i);
    /// \brief Accesses the character at position i in the string.
    /// \throw std::out_of_range if `i` is an invalid index
    char at(std::size_t i) const;
    /// \brief True if the string is empty, i.e. has length 0
    bool empty() const noexcept;
    /// \brief Size or length of the string.
    std::size_t size() const noexcept;
    /// \brief Length or size of the string.
    std::size_t length() const noexcept;

    /// \brief A unique_ptr managed char[] containing a copy of the data of the string,
    /// guaranteed to be null-terminated.
    std::unique_ptr<char> as_c_string() const;
    /// \brief A copy of this string represented as a std::string.
    std::string as_std_string() const;

    /// \brief Clears the contents of the string, resulting string will be the empty string.
    void clear();

    /// \brief Inserts a char before the position pointed to by the iterator. May invalidate
    /// iterators.
    void insert(ConstIterator iter, char c);
    /// \brief Inserts the string before the position pointed to by the iterator. May invalidate
    /// iterators.
    void insert(ConstIterator iter, const String& s);
    /// \brief Inserts the part of the string specified by the begin and end iterators
    /// before the position pointed to by the "iter" iterator. May invalidate iterators.
    void insert(ConstIterator iter, ConstIterator begin, ConstIterator end);

    /// \brief Removes the element pointed to by the iterator. Invalidates iterators.
    void erase(ConstIterator iter);
    /// \brief Removes elements between from and to. Invalidates iterators.
    void erase(ConstIterator from, ConstIterator to);
    /// \brief Removes n elements starting at the iterator position. Invalidates iterators.
    void erase(ConstIterator iter, std::size_t n);

    /// \brief A copy of the chars between from and to, as a new string.
    String substring(ConstIterator from, ConstIterator to) const;
    /// \brief A copy of the first n chars from start, as a new string.
    String substring(ConstIterator start, std::size_t n) const;

    /// \brief Finds the first occurance of char c in the string. Returns end() if nothing was
    /// found.
    /// \arg `c` character to find, case-sensitive.
    /// \return String::Iterator pointing to the found character, or end() if nothing was found.
    Iterator find(char c);
    /// \brief Finds the first occurance of char c in the string. Returns end() if nothing was
    /// found.
    /// \arg `c` character to find, case-sensitive.
    /// \return String::ConstIterator pointing to the found character, or end() if nothing was found.
    ConstIterator find(char c) const;
    /// \brief Finds the first occurance of char c in the string, ignoring case. Returns end() if
    /// nothing was found. Default locale is "C".
    /// \arg `c` character to find
    /// \arg `locale` locale to use when considering and converting case
    /// \return String::Iterator pointing to the found character, or end() if nothing was found
    Iterator find_caseless(char c, const std::locale& locale = std::locale::classic());
    /// \brief Finds the first occurance of char c in the string, ignoring case. Returns end() if
    /// nothing was found. Default locale is "C".
    /// \arg `c` character to find
    /// \arg `locale` locale to use when considering and converting case
    /// \return String::ConstIterator pointing to the found character, or end() if nothing was found
    ConstIterator find_caseless(char c, const std::locale& locale = std::locale::classic()) const;

    /// \brief Finds the first occurance of the string inside this string.
    /// \return String::Iterator pointing to the beginning of the found substring, or end() if
    /// nothing was found
    Iterator find(const String&);
    /// \brief Finds the first occurance of the string inside this string.
    /// \return String::ConstIterator pointing to the beginning of the found substring, or end() if
    /// nothing was found
    ConstIterator find(const String&) const;
    /// \brief Finds the first occurance of the string after `start` inside this string.
    /// \return String::Iterator pointing to the beginning of the found substring, or end() if
    /// nothing was found
    Iterator find(const String&, Iterator start);
    /// \brief Finds the first occurance of the string after `start` inside this string.
    /// \return String::ConstIterator pointing to the beginning of the found substring, or end() if
    /// nothing was found
    ConstIterator find(const String&, ConstIterator start) const;
    
    /// \brief Whether this string contains the substring.
    bool contains(const String&) const;
    /// \brief Whether this string starts with the substring.
    bool startswith(const String&) const;

    /// \brief Does a case-sensitive comparison between the chars of both strings.
    /// Same as String::operator==(const String&).
    bool equals(const String&) const;
    /// \brief Does a case-sensitive comparison between the chars of both strings.
    bool operator==(const String&) const;
    /// \brief Does a case-sensitive comparison between the chars of both strings.
    bool operator!=(const String&) const;

    /// \brief Appends the given string to this string.
    String& operator+=(const String&);
    /// \brief Creates a new string by appending a string to this string.
    String operator+(const String&) const;

    /// \brief Replaces \b all instances of `to_replace` with `replace_with` in the string.
    void replace(char to_replace, char replace_with);
    /// \brief Replaces \b all instances of `to_replace` with `replace_with` in the string.
    void replace(const String& to_replace, const String& replace_with);
    /// \brief Replaces `n` instances of `to_replace` with `replace_with` in the string.
    void replace(const String& to_replace, const String& replace_with, std::size_t n);

    friend std::ostream& operator<<(std::ostream&, const String&);
};

#endif // STRING_H
