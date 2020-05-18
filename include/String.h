#ifndef STRING_H
#define STRING_H

#include <cstdarg>
#include <iostream>
#include <memory>
#include <vector>

class String
{
private:
    std::vector<char> m_chars;

public:
    /// New empty string, equivalent to String("")(
    String();
    /// New string with cstr as content
    String(const char* cstr);

    String(const String&) = default;
    String(String&&)      = default;
    String& operator=(const String&) = default;

    using Iterator      = char*;
    using ConstIterator = const char*;

    Iterator      begin();
    ConstIterator begin() const;
    Iterator      end();
    ConstIterator end() const;
    char&         at(std::size_t i);
    char          at(std::size_t i) const;
    bool          empty() const;
    std::size_t   size() const;
    std::size_t   length() const;

    std::unique_ptr<char> as_c_string() const;

    void clear();
    void insert(ConstIterator iter, char c);
    void insert(ConstIterator iter, const String& s);
    void insert(ConstIterator iter, ConstIterator begin, ConstIterator end);
};

#endif // STRING_H
