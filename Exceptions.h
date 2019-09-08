#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class InvalidAppendAfterBuild : public std::exception
{
public:
    virtual const char* what() const noexcept
    {
        return "StringBuilder: Append after build not allowed!";
    }
};

#endif // EXCEPTIONS_H
