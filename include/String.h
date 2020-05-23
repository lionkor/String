#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <memory>
#include <charconv>
#include <vector>
#include <cstring>
#include <sstream>

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
/// to convert to a `std::string` or c-string via `String::to_c_string` and `String::to_std_string`.
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

    /// \brief New empty string, equivalent to `""`.
    String();
    /// \brief New string from nullptr -> empty string.
    String(std::nullptr_t);
    /// \brief New string with only the char `c`.
    explicit String(char c);
    /// \brief New string with cstr as content
    String(const char* cstr);
    /// \brief New string from another string's iterators.
    String(ConstIterator from, ConstIterator to);

    String(const String&) = default;
    String(String&&)      = default;
    String& operator=(const String&) = default;

    /// \brief Implicit conversion to std::string allowed.
    operator std::string() const;

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
    std::unique_ptr<char[]> to_c_string() const;
    /// \brief A copy of this string represented as a std::string.
    std::string to_std_string() const;

    /// \brief Clears the contents of the string, resulting string will be the empty string.
    void clear() noexcept;

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
    /// \brief Finds the first occurance of char c in the string after `start`. Returns end() if nothing was
    /// found.
    /// \arg `c` character to find, case-sensitive.
    /// \arg `start` position from which to search from.
    /// \return String::Iterator pointing to the found character, or end() if nothing was found.
    Iterator find(char c, Iterator start);
    /// \brief Finds the first occurance of char c in the string after `start`. Returns end() if nothing was
    /// found.
    /// \arg `c` character to find, case-sensitive.
    /// \arg `start` position from which to search from.
    /// \return String::ConstIterator pointing to the found character, or end() if nothing was found.
    ConstIterator find(char c, ConstIterator start) const;

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
    /// \brief Whether this string ends with the substring.
    bool endswith(const String&) const;

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

    /// \brief Splits the String into substrings delimited by `delim`.
    ///
    /// \arg `delim` delimiter to be used
    /// \arg `expected_splits` how many parts are expected. Setting this to a reasonable
    /// amount will speed up the split operation as memory can be reserved beforehand.
    std::vector<String> split(char delim, std::size_t expected_splits = 2) const;
    /// \brief Splits the String into substrings delimited by the String `delim`.
    ///
    /// \arg `delim` delimiter string to be used
    /// \arg `expected_splits` how many parts are expected. Setting this to a reasonable
    /// amount will speed up the split operation as memory can be reserved beforehand.
    std::vector<String> split(const String& delim, std::size_t expected_splits = 2) const;

    /// \brief Grows the capacity to fit `size` many characters. Does not change the size of the string.
    ///
    /// Increases the capacity of the currently allocated memory to be able to hold `size` many
    /// characters before having to reallocate. Calling this before doing a lot of appending up to a known
    /// max length can increase performance significantly, as multiple allocations are avoided.
    /// Does not impact length.
    void reserve(std::size_t size);

    /// \brief Capacity of the string's underlying allocated memory.
    ///
    /// The String's size may grow up to this capacity without any reallocation taking place.
    std::size_t capacity() const;

    /// \brief Shrinks capacity to be equal to size, thus freeing memory in some cases. Not
    /// guaranteed, as it's implementation dependent.
    void shrink_to_fit() noexcept;

    /// \brief Raw pointer to the data of this String.
    /// Keep in mind that this is NOT null-terminated.
    char* data() noexcept;
    /// \brief Raw const pointer to the data of this String.
    /// Keep in mind that this is NOT null-terminated.
    const char* data() const noexcept;

    friend std::ostream& operator<<(std::ostream&, const String&);
    friend std::istream& operator>>(std::istream& is, String& s);

    /// \brief Constructs a string from non-string arguments.
    ///
    /// Accepts and correctly formats any type `T` for which an overload for
    ///
    ///     std::ostream& operator<<(std::ostream&, T)
    ///
    /// exists. Arguments will be appended to the String in order.
    /// Pass String::Format to specify floating point precision, width, fill
    /// chars, base, etc.
    template<class... Args>
    static String format(Args&&... things) {
        std::stringstream s;
        return format(s, std::forward<Args>(things)...);
    }

    /// \brief Specifies the formatting of a String::format operation.
    ///
    /// Example
    ///
    ///     String::Format fmt;
    ///     fmt.precision = 3;
    ///     String my_string = String::format(fmt, 2.1337);
    ///
    /// will result in
    ///
    ///     my_string = "2.13"
    ///
    struct Format {
        enum Align : bool
        {
            Left,
            Right
        };

        enum Base
        {
            Oct = 8,
            Dec = 10,
            Hex = 16,
        };

        /// \brief The precision (i.e. how many digits are generated) of floating
        /// point numbers output with this format. See `std::ios::precision`.
        int precision { 6 };
        /// \brief The base used to display integer types. See `std::ios::base`.
        Base base { Base::Dec };
        /// \brief Alignment used with width. See `std::ios::left` and `std::ios::right`.
        Align alignment { Align::Left };
        /// \brief Width used on some format operations. See `std::ios::width`.
        int width { 0 };
        /// \brief Filler used to fill whitespace in width formats. See `std::ios::fill`.
        char fill { ' ' };

        friend std::ostream& operator<<(std::ostream&, const Format&);
    };

private:
    static String format(std::stringstream& is) {
        String s;
        is >> s;
        return s;
    }

    template<class... Args, class T>
    static String format(std::stringstream& is, T&& t, Args&&... things) {
        is << t;
        return format(is, std::forward<Args>(things)...);
    }
};


/// \brief Null-terminated, fully constexpr string that will almost completely disappear with
/// compiler optimizations turned on.
///
/// To be used for string constants, as it's as fast as declaring a `const char*`
/// but knows its own size and can be compared with operator==, which is optimized
/// into constants at compile-time.
class ConstString
{
private:
    const char*       m_buffer;
    const std::size_t m_size;

    static constexpr std::size_t length(const char* str) {
        return *str ? 1 + length(str + 1) : 0;
    }

public:
    /// \brief Initialization with nullptr is not allowed.
    constexpr ConstString(std::nullptr_t) = delete;
    /// \brief New ConstString from a string literal.
    constexpr ConstString(const char*&& buffer)
        : m_buffer(buffer)
        , m_size(length(buffer)) {
    }

    /// \brief Size, aka length, of the string.
    constexpr auto size() const { return m_size; }
    /// \brief Length, aka size, of the string.
    constexpr auto length() const { return m_size; }

    /// \brief Allows implicit conversion to `const char*`.
    constexpr operator const char*() const { return m_buffer; }

    /// \brief Comparison with other `char*`-like types.
    template<class T>
    constexpr bool operator==(const T str) const {
        return std::strcmp(m_buffer, str) == 0;
    }

    /// \brief Comparison with the String type.
    bool operator==(const String& str) const {
        return m_size != str.size() || std::strncmp(m_buffer, str.data(), m_size) == 0;
    }
};

#endif // STRING_H
