#include "String.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iomanip>

String::String() { }

String::String(std::nullptr_t) { }

String::String(char c) {
    m_chars.push_back(c);
}

String::String(const char* cstr)
    : m_chars(cstr, cstr + std::strlen(cstr)) {
}

String::String(String::ConstIterator from, String::ConstIterator to)
    : m_chars(from, to) {
}

String::operator std::string() const {
    return as_std_string();
}

String::Iterator String::begin() {
    return m_chars.begin();
}

String::Iterator String::end() {
    return m_chars.end();
}

String::ConstIterator String::begin() const {
    return m_chars.begin();
}

String::ConstIterator String::end() const {
    return m_chars.end();
}

char& String::at(std::size_t i) {
    return m_chars.at(i);
}

bool String::empty() const noexcept {
    return m_chars.empty();
}

std::size_t String::size() const noexcept {
    return m_chars.size();
}

std::size_t String::length() const noexcept {
    return m_chars.size();
}

char String::at(std::size_t i) const {
    return m_chars.at(i);
}

std::unique_ptr<char> String::as_c_string() const {
    auto ptr = std::unique_ptr<char>(new char[m_chars.size() + 1]);
    std::copy_n(m_chars.data(), m_chars.size(), ptr.get());
    ptr.get()[m_chars.size()] = '\0';
    return ptr;
}

std::string String::as_std_string() const {
    return std::string(m_chars.begin(), m_chars.end());
}

void String::clear() noexcept {
    m_chars.clear();
}

void String::insert(String::ConstIterator iter, const String& s) {
    if (iter > end())
        throw std::runtime_error("iterator out of range");
    m_chars.insert(iter, s.begin(), s.end());
}

void String::insert(String::ConstIterator iter, String::ConstIterator begin, String::ConstIterator end) {
    if (iter > this->end())
        throw std::runtime_error("iterator out of range");
    m_chars.insert(iter, begin, end);
}

void String::insert(String::ConstIterator iter, char c) {
    if (iter > end())
        throw std::runtime_error("iterator out of range");
    m_chars.insert(iter, c);
}

void String::erase(String::ConstIterator iter) {
    if (iter < begin() || iter > end() || empty() || iter == end())
        throw std::runtime_error("iterator out of range");
    m_chars.erase(iter);
}

void String::erase(String::ConstIterator from, String::ConstIterator to) {
    if (from < begin() || from > end() || empty() || from == end() || to < begin() || to > end() || to < from)
        throw std::runtime_error("iterator out of range");
    m_chars.erase(from, to);
}

void String::erase(String::ConstIterator iter, std::size_t n) {
    erase(iter, iter + n);
}

String String::substring(String::ConstIterator from, String::ConstIterator to) const {
    return String(from, to);
}

String String::substring(String::ConstIterator start, std::size_t n) const {
    return String(start, start + n);
}

String::Iterator String::find(char c) {
    return std::find(m_chars.begin(), m_chars.end(), c);
}

String::ConstIterator String::find(char c) const {
    return std::find(m_chars.begin(), m_chars.end(), c);
}

String::Iterator String::find(char c, String::Iterator start) {
    return std::find(start, m_chars.end(), c);
}

String::ConstIterator String::find(char c, String::ConstIterator start) const {
    return std::find(start, m_chars.end(), c);
}

String::Iterator String::find_caseless(char c, const std::locale& locale) {
    return std::find_if(m_chars.begin(), m_chars.end(), [c, locale](const auto& a) -> bool {
        return std::tolower(a, locale) == std::tolower(c, locale);
    });
}

String::ConstIterator String::find_caseless(char c, const std::locale& locale) const {
    return std::find_if(m_chars.begin(), m_chars.end(), [c, locale](const auto& a) -> bool {
        return std::tolower(a, locale) == std::tolower(c, locale);
    });
}

String::Iterator String::find(const String& str) {
    return std::search(begin(), end(), str.begin(), str.end());
}

String::ConstIterator String::find(const String& str) const {
    return std::search(begin(), end(), str.begin(), str.end());
}

String::Iterator String::find(const String& str, Iterator start) {
    return std::search(start, end(), str.begin(), str.end());
}

String::ConstIterator String::find(const String& str, String::ConstIterator start) const {
    return std::search(start, end(), str.begin(), str.end());
}

bool String::contains(const String& str) const {
    if (str.size() > size())
        return false;
    return find(str) != end();
}

bool String::startswith(const String& str) const {
    if (str.size() > size())
        return false;
    return std::equal(begin(), begin() + str.size(), str.begin(), str.end());
}

bool String::endswith(const String& str) const {
    if (str.size() > size())
        return false;
    return std::equal(end() - str.size(), end(), str.begin(), str.end());
}

bool String::equals(const String& str) const {
    if (size() != str.size())
        return false;
    return std::equal(begin(), end(), str.begin(), str.end());
}

bool String::operator==(const String& s) const {
    return equals(s);
}

bool String::operator!=(const String& s) const {
    return !equals(s);
}

String& String::operator+=(const String& s) {
    insert(end(), s);
    return *this;
}

String String::operator+(const String& s) const {
    String result = *this;
    result.insert(result.end(), s);
    return result;
}

void String::replace(char to_replace, char replace_with) {
    for (auto& c : m_chars)
        if (c == to_replace)
            c = replace_with;
}

void String::replace(const String& to_replace, const String& replace_with) {
    if (!to_replace.empty() && replace_with.find(to_replace) != replace_with.end())
        throw std::invalid_argument("replace_with shall not contain to_replace");
    Iterator iter;
    do {
        iter = std::search(begin(), end(), to_replace.begin(), to_replace.end());
        if (iter != end()) {
            erase(iter, to_replace.size());
            insert(iter, replace_with);
        }
    } while (iter != end());
}

void String::replace(const String& to_replace, const String& replace_with, std::size_t n) {
    if (!to_replace.empty() && replace_with.find(to_replace) != replace_with.end())
        throw std::invalid_argument("replace_with shall not contain to_replace");
    Iterator    iter;
    std::size_t i = 0;
    do {
        if (i >= n)
            break;
        ++i;
        iter = std::search(begin(), end(), to_replace.begin(), to_replace.end());
        if (iter != end()) {
            erase(iter, to_replace.size());
            insert(iter, replace_with);
        }
    } while (iter != end());
}

std::vector<String> String::split(char delim, std::size_t expected_splits) const {
    std::vector<String> result;
    result.reserve(expected_splits);
    // FIXME: is this undefined?
    auto last_iter = begin() - 1;
    auto iter      = find(delim);
    while (last_iter != end()) {
        // +1 skips the delimiter itself
        result.push_back(String(last_iter + 1, iter));
        last_iter = iter;
        iter = find(delim, iter + 1);
    }
    return result;
}

void String::reserve(std::size_t size) {
    m_chars.reserve(size);
}

std::size_t String::capacity() const {
    return m_chars.capacity();
}

void String::shrink_to_fit() noexcept {
    m_chars.shrink_to_fit();
}

char* String::data() noexcept {
    return m_chars.data();
}

const char* String::data() const noexcept {
    return m_chars.data();
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    return os << s.as_std_string();
}

std::istream& operator>>(std::istream& is, String& s) {
    const auto len = is.rdbuf()->pubseekoff(0, std::ios::end);
    is.rdbuf()->pubseekoff(0, std::ios::beg);
    const auto offset = s.m_chars.size();
    s.m_chars.resize(s.m_chars.size() + len);
    auto ret = is.rdbuf()->sgetn(s.m_chars.data() + offset, len);
    static_cast<void>(ret);
    is.rdbuf()->pubseekoff(0, std::ios::end);
    return is;
}

std::ostream& operator<<(std::ostream& os, const String::Format& fmt) {
    switch (fmt.alignment) {
    case String::Format::Align::Left:
        os << std::left;
        break;
    case String::Format::Align::Right:
        os << std::right;
    }

    os << std::setprecision(fmt.precision)
       << std::setbase(fmt.base)
       << std::setw(fmt.width)
       << std::setfill(fmt.fill);

    return os;
}
