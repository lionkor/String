#ifndef STRINGVIEW_H
#define STRINGVIEW_H

#include <cassert>
#include <cstring>
#include <ostream>

using size_t = unsigned long;

static inline constexpr std::size_t string_length(const char* cstr)
{
	assert(cstr != nullptr);
	std::size_t length = 0;
	while (*cstr != '\0')
	{
		length++;
		cstr++;
	}
	return length;
}

template<typename _T>
static inline constexpr _T min(_T&& left, _T&& right)
{
	return left < right ? left : right;
}

/// View to a null-terminated string.
class StringView
{
public:
	constexpr StringView() : m_chars(nullptr), m_size(0) {}
	constexpr StringView(const char* cstr) : m_chars(cstr), m_size(string_length(cstr)) {}
	constexpr StringView(const StringView& other)
		: m_chars(other.m_chars), m_size(other.m_size)
	{
	}
	constexpr StringView(const char* begin, const char* end);
	StringView(const class String&);

protected:
	/// Caution: The given const char* still has to be null-terminated exactly at the
	/// given size, otherwise behaviour of StringView isn't defined.
	constexpr StringView(const char* cs, std::size_t sz) : m_chars(cs), m_size(sz) {}

public:
	inline constexpr bool	is_valid() const { return m_chars != nullptr; }
	inline constexpr bool	is_empty() const { return m_size == 0 || m_chars[0] == 0; }
	inline constexpr size_t size() const { return m_size; }
	inline constexpr const char* chars() const { return m_chars; }
	inline constexpr const char* c_str() const { return m_chars; }

	constexpr const char& operator[](std::size_t i) const { return m_chars[i]; }

	inline constexpr bool equals(const char* str, std::size_t size) const
	{
		// if one is nullptr and the other isn't, they aren't equal
		if ((m_chars == nullptr && str != nullptr) ||
			(m_chars != nullptr && str == nullptr))
			return false;
		// if they are both nullptr we consider them equal
		if (m_chars == nullptr && str == nullptr)
			return true;
		// if other is larger than our size we aren't equal. If we didn't have this check,
		// strncmp would return 0 (equal) for example for:
		//  strncmp("Hello", "Hello, World", strlen("Hello")), since "Hello" would have
		//  size 5, and they equal that far.
		// Similarly, if it's shorter, they aren't equal. If we're going to check length
		// we might as well check this as well and potentially save ourselves a strncmp.
		if (size != m_size)
			return false;
		// Because of earlier checks we can now assume same size and that both are not
		// nullptr.
		return strncmp(m_chars, str, m_size) == 0;
	}
    
	constexpr bool operator==(const char* other) const
	{
		return equals(other, strlen(other));
	}

	constexpr bool operator==(const StringView& other) const
	{
		return equals(other.m_chars, other.m_size);
	}

    template<typename _StringType>
    constexpr bool operator==(const _StringType& other) const
    {
        return equals(other.c_str(), other.size());
    }

	constexpr bool operator!=(const char* other) const { return !(*this == other); }

	constexpr bool operator!=(const StringView& other) const { return !(*this == other); }

    template<typename _StringType>
    constexpr bool operator!=(const _StringType& other) const
    {
        return !(*this == other);
    }
    
	friend std::ostream& operator<<(std::ostream& os, const StringView& view)
	{
		if (view.m_chars)
			return os << view.m_chars;
		else
			return os << "";
	}

	friend constexpr StringView operator""_sv(const char* cstr, unsigned long size);

private:
	const char*	 m_chars;
	const size_t m_size;
};

constexpr StringView::StringView(const char* begin, const char* end)
	: m_chars(begin), m_size(end - begin)
{
}

constexpr StringView operator""_sv(const char* cstr, unsigned long size)
{
	return StringView(cstr, size);
}

#endif // STRINGVIEW_H
