#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class StringBuilder_InvalidChangeAfterBuild : public std::exception
{
public:
	virtual const char* what() const noexcept
	{
		return "StringBuilder: Append after build not allowed!";
	}
};

class StringBuilder_DoubleBuildNotAllowed : public std::exception
{
public:
	virtual const char* what() const noexcept
	{
		return "StringBuilder: Can only build once - StringBuilder has already "
			   "transferred ownership!";
	}
};

class FormatEncodingError : public std::exception
{
public:
	virtual const char* what() const noexcept
	{
		// Helping the user guess what happened.
		return "Format encoding failed. Possibly invalid format passed or wrong type?";
	}
};

class FormatWriteFault : public std::exception
{
public:
	virtual const char* what() const noexcept
	{
		return "Writing formatted string was not successful. (vsnprintf returned >=n)";
	}
};

#endif // EXCEPTIONS_H
