#include "String.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>

String::String()
    : m_chars(0) { }

String::String(const char* cstr) {
    if (cstr) {
        m_chars.resize(std::strlen(cstr));
        std::copy_n(cstr, m_chars.size(), m_chars.begin());
    }
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

bool String::empty() const {
    return m_chars.empty();
}

std::size_t String::size() const {
    return m_chars.size();
}

std::size_t String::length() const {
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

void String::clear() {
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

void String::erase_from_to(String::ConstIterator from, String::ConstIterator to) {
    if (from < begin() || from > end() || empty() || from == end() || to < begin() || to > end() || to < from)
        throw std::runtime_error("iterator out of range");
    m_chars.erase(from, to);
}

void String::erase_n(String::ConstIterator iter, std::size_t n) {
    erase_from_to(iter, iter + n);
}

