#include "StringBuilder.h"
#include "Exceptions.h"

StringBuilder::StringBuilder()
    : m_size(0), 
      m_chars(std::make_unique<char[]>(m_size+1)) // FIXME: Do we need to initialize it here?
{
}

StringBuilder::StringBuilder(const StringBuilder& builder)
    : m_size(builder.m_size), m_chars(std::make_unique<char[]>(m_size+1))
{
    std::strcpy(m_chars.get(), builder.m_chars.get());
}

StringBuilder::~StringBuilder()
{
}

void StringBuilder::append(const char* cstr)
{
    if (m_built) throw StringBuilder_InvalidAppendAfterBuild();
    std::unique_ptr<char[]> new_chars = std::make_unique<char[]>(m_size + std::strlen(cstr) + 1);
    if (m_size != 0)
    {
        std::strcpy(new_chars.get(), m_chars.get());
        std::strcat(new_chars.get(), cstr);
    }
    else
    {
        std::strcpy(new_chars.get(), cstr);
    }
    m_chars = std::move(new_chars);
    m_size = std::strlen(m_chars.get());
}

void StringBuilder::append(char c)
{
    if (m_built) throw StringBuilder_InvalidAppendAfterBuild();
    auto new_chars = std::make_unique<char[]>(m_size + 1 + 1);
    if (m_size != 0)
    {
        std::strcpy(new_chars.get(), m_chars.get());
        new_chars[m_size] = c;
        new_chars[m_size + 1] = '\0';
    }
    else
    {
        new_chars[0] = c;
        new_chars[1] = '\0';
    }
    m_chars = std::move(new_chars);
    m_size += 1;
}

void StringBuilder::append(const String& str)
{
    append(str.c_str());
}

void StringBuilder::prepend(const char * cstr)
{
    if (m_built) throw StringBuilder_InvalidAppendAfterBuild();
    auto new_chars = std::make_unique<char[]>(m_size + std::strlen(cstr) + 1);
    if (m_size != 0)
    {
        std::strcpy(new_chars.get(), cstr);
        std::strcat(new_chars.get(), m_chars.get());
    }
    else
    {
        std::strcpy(new_chars.get(), cstr);
    }
    m_chars = std::move(new_chars);
    m_size = std::strlen(m_chars.get());
}

void StringBuilder::prepend(char c)
{
    if (m_built) throw StringBuilder_InvalidAppendAfterBuild();
    auto new_chars = std::make_unique<char[]>(m_size + 1 + 1);
    if (m_size != 0)
    {
        new_chars[0] = c;
        new_chars[1] = '\0';
        std::strcat(new_chars.get(), m_chars.get());
    }
    else
    {
        new_chars[0] = c;
        new_chars[1] = '\0';
    }
    m_chars = std::move(new_chars);
    m_size += 1;
}

void StringBuilder::prepend(const String & str)
{
    prepend(str.c_str());
}

void StringBuilder::appendf(const char* fmt, ...)
{
    /* NOTE:
     * This sucks. It should not use varargs.
     * Format Strings are a bad idea.
     * I know this, and I am working on a better way to do this.
     * See FIXME below.
     */
    
    // FIXME: Rewrite this to use variadic templates.

    
    va_list args;
    va_start(args, fmt);
    int size = std::vsnprintf (NULL, 0, fmt, args);
    
    // vsnprintf returns <0 if encoding error occured.
    if (size < 0) throw FormatEncodingError();
    
    va_end (args); 
    va_start(args, fmt);
    auto buf = std::make_unique<char[]>(size + 1);
    int rc = std::vsnprintf (buf.get(), size + 1, fmt, args);
    
    // vsnprintf returns <0 if encoding error occured.
    if (rc < 0) throw FormatEncodingError();
    
    // vsnprintf returns >0 and <n on success. 
    // This is sadly a super generic error.
    if (rc >= size+1) throw FormatWriteFault(); 
    
    va_end (args);
    append (buf.get());
}

void StringBuilder::prependf(const char* fmt, ...)
{
    // FIXME: Unhandled possible failures (might return 0, etc).
    va_list args;
    va_start(args, fmt);
    unsigned size = std::vsnprintf (NULL, 0, fmt, args);
    va_end (args); 
    va_start(args, fmt);
    auto buf = std::make_unique<char[]>(size + 1);
    std::vsnprintf (buf.get(), size + 1, fmt, args);
    va_end (args);
    prepend (buf.get());
}

String StringBuilder::build()
{
    if (m_built) throw StringBuilder_DoubleBuildNotAllowed();
    String s {};
    s.m_size = m_size;
    // Transfer ownership.
    //  This is why we cannot build more than once.
    s.m_chars = std::move(m_chars); 
    m_built = true;
    return s;
}

StringBuilder& StringBuilder::operator=(const StringBuilder& builder)
{
    m_chars = std::make_unique<char[]>(builder.m_size + 1);
    std::strcpy(m_chars.get(), builder.m_chars.get());
    m_size = builder.m_size;
    m_built = builder.m_built;
    return *this;
}
