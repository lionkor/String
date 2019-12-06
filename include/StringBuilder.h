#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include <cstdarg>
#include <cstring>
#include <memory>

#include "Exceptions.h"
#include "Core.h"

class StringBuilder
{
public:
	/// Ctor.
	StringBuilder();
	/// Move ctor.
	StringBuilder(StringBuilder&&);
	/// Dtor.
	virtual ~StringBuilder();

	StringBuilder(const StringBuilder&) = delete;

	StringBuilder& append(const char*);
	StringBuilder& append(const class String&);
	StringBuilder& append(char);
	StringBuilder& append(int);
	StringBuilder& append(short);
	StringBuilder& append(unsigned short);
	StringBuilder& append(long);
	StringBuilder& append(unsigned);
	StringBuilder& append(unsigned long);
	StringBuilder& append(unsigned long long);
	StringBuilder& append(unsigned char);
	StringBuilder& append(float);
	StringBuilder& append(float, unsigned precision);
	StringBuilder& append(double);
	StringBuilder& append(long double);
	StringBuilder& append(const PointerFormat& arg);

	StringBuilder& prepend(const char*);
	StringBuilder& prepend(const class String&);
	StringBuilder& prepend(char);
	StringBuilder& prepend(int);
	StringBuilder& prepend(short);
	StringBuilder& prepend(unsigned short);
	StringBuilder& prepend(long);
	StringBuilder& prepend(unsigned);
	StringBuilder& prepend(unsigned long);
	StringBuilder& prepend(unsigned long long);
	StringBuilder& prepend(unsigned char);
	StringBuilder& prepend(float);
	StringBuilder& prepend(double);
	StringBuilder& prepend(long double);
	StringBuilder& prepend(const PointerFormat& arg);

	template<typename _T>
	StringBuilder& append(const HexFormat<_T>& arg);
	template<typename _T>
	StringBuilder& prepend(const HexFormat<_T>& arg);

	template<typename _T>
	StringBuilder& append(const OctalFormat<_T>& arg);
	template<typename _T>
	StringBuilder& prepend(const OctalFormat<_T>& arg);

	/// Builds the String and returns it.
	[[nodiscard]] class String build();

	StringBuilder& operator=(StringBuilder&&);

	/// Returns the current contents of the char* data.
	const char* c_str() const { return m_chars; }

private:
	inline void store(const char* cstr)
	{
		ASSERT(cstr);
		ASSERT(m_chars);

		if (cstr == m_chars)
			return;
		if (std::strcmp(cstr, m_chars) == 0)
			return;

		std::size_t new_size = std::strlen(cstr);
		if (new_size > m_capacity)
		{
			m_capacity		= new_size;
			char* new_chars = new char[m_capacity + 1];
			std::strcpy(new_chars, cstr);
			delete[] m_chars;
			std::swap(m_chars, new_chars);
		}
		else
		{
			std::strcpy(m_chars, cstr);
		}
		m_size = new_size;
	}

	inline void concat(const char* first, const char* second)
	{
		std::size_t first_size	= std::strlen(first);
		std::size_t second_size = std::strlen(second);
		std::size_t new_size	= first_size + second_size;

		if (new_size >= m_capacity)
		{
			// make sure we allocate multiple of 8 for sanity
			m_capacity		= new_size % 8 == 0 ? new_size : (new_size / 8) * 8 + 7;
			char* new_chars = new char[m_capacity + 1] { 0 };
			std::memset(new_chars, 0, sizeof(char) * m_capacity);
			std::strcpy(new_chars, first);
			std::strcat(new_chars, second);
			delete[] m_chars;
			std::swap(m_chars, new_chars);
		}
		else
		{
			if (first == m_chars)
			{
				std::strcat(m_chars, second);
			}
			else
			{
				std::memcpy(m_chars + first_size, second, second_size);
				std::memcpy(m_chars, first, first_size);
			}
		}
		m_size = new_size;
	}

	std::size_t m_size;
	std::size_t m_capacity;
	char*		m_chars { nullptr };
	bool		m_built { false };
};

template<typename _T>
StringBuilder& StringBuilder::append(const HexFormat<_T>& arg)
{
	if (m_built)
		throw StringBuilder_InvalidChangeAfterBuild();
	char tmp[16] { 0 };
	sprintf(tmp, "%x", arg.data);
	return append(tmp);
}

template<typename _T>
StringBuilder& StringBuilder::prepend(const HexFormat<_T>& arg)
{
	if (m_built)
		throw StringBuilder_InvalidChangeAfterBuild();
	char tmp[16] { 0 };
	sprintf(tmp, "%x", arg.data);
	return prepend(tmp);
}

template<typename _T>
StringBuilder& StringBuilder::append(const OctalFormat<_T>& arg)
{
	if (m_built)
		throw StringBuilder_InvalidChangeAfterBuild();
	char tmp[16] { 0 };
	sprintf(tmp, "%o", arg.data);
	return append(tmp);
}

template<typename _T>
StringBuilder& StringBuilder::prepend(const OctalFormat<_T>& arg)
{
	if (m_built)
		throw StringBuilder_InvalidChangeAfterBuild();
	char tmp[16] { 0 };
	sprintf(tmp, "%o", arg.data);
	return prepend(tmp);
}

#endif // STRINGBUILDER_H
