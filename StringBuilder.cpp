#include "StringBuilder.h"
#include "Exceptions.h"
#include <cctype>

#define DEBUG_STRING_BUILDER

#ifdef DEBUG_STRING_BUILDER
    #define log_strbuild(x) std::cout << "[DEBUG] StringBuilder:" << __LINE__ << ": " << x << std::endl
#else
    #define log_strbuild(x)
#endif

StringBuilder::StringBuilder()
{
    store("");
}

StringBuilder::StringBuilder(const StringBuilder& builder)
{
    store(builder.chars(), builder.size());
}

StringBuilder::~StringBuilder() {}

void internal_strcat(char*& dest, const char* src, std::size_t insertion_start)
{
    for (std::size_t i = 0; src[i] != 0; ++i, ++src)
    {
        log_strbuild(i);
        dest[i + insertion_start] = src[i];
    }
}

void StringBuilder::append(const char* cstr)
{
    log_strbuild(__PRETTY_FUNCTION__ << " with cstr = _" << cstr << "_");
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();
    
    printf("=== DUMP BEFORE STRCAT ===\n");
    for (int i = 0; i < MAX_ALLOC; ++i)
    {
        printf("%3i ", chars()[i]);
    }
    std::cout << std::endl;
    for (int i = 0; i < MAX_ALLOC; ++i)
    {
        if (isprint(chars()[i]))
            printf("%3c ", chars()[i]);
        else
            printf("%3c ", '?');
    }
    printf("\n==========================\n");
    
    std::size_t delta = strlen(cstr);
    resize(delta);
    sprintf(chars(), "%s%s", chars(), cstr);

    printf("=== DUMP AFTER STRCAT ===\n");
    for (int i = 0; i < MAX_ALLOC; ++i)
    {
        printf("%3i ", chars()[i]);
    }
    std::cout << std::endl;
    for (int i = 0; i < MAX_ALLOC; ++i)
    {
        if (isprint(chars()[i]))
            printf("%3c ", chars()[i]);
        else
            printf("%3c ", '?');
    }
    printf("\n=========================\n");
}

void StringBuilder::append(char c)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();
    std::size_t new_size = size() + 1;
    sprintf(chars(), "%s%c", chars(), c);
}

void StringBuilder::append(const String& str) { append(str.chars()); }

void StringBuilder::prepend(const char* cstr)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();
    auto new_chars = std::make_unique<char[]>(size() + std::strlen(cstr) + 1);
    if (size() != 0)
    {
        std::strcpy(new_chars.get(), cstr);
        std::strcat(new_chars.get(), chars());
    }
    else
    {
        std::strcpy(new_chars.get(), cstr);
    }
    //m_chars = std::move(new_chars);
    //size() = std::strlen(chars());
}

void StringBuilder::prepend(char c)
{
    if (m_built)
        throw StringBuilder_InvalidAppendAfterBuild();
    auto new_chars = std::make_unique<char[]>(size() + 1 + 1);
    if (size() != 0)
    {
        new_chars[0] = c;
        new_chars[1] = '\0';
        std::strcat(new_chars.get(), chars());
    }
    else
    {
        new_chars[0] = c;
        new_chars[1] = '\0';
    }
    //m_chars = std::move(new_chars);
    //size() += 1;
}

void StringBuilder::prepend(const String& str) { prepend(str.chars()); }

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
    int size = std::vsnprintf(NULL, 0, fmt, args);

    // vsnprintf returns <0 if encoding error occured.
    if (size < 0)
        throw FormatEncodingError();

    va_end(args);
    va_start(args, fmt);
    auto buf = std::make_unique<char[]>(size + 1);
    int rc = std::vsnprintf(buf.get(), size + 1, fmt, args);

    // vsnprintf returns <0 if encoding error occured.
    if (rc < 0)
        throw FormatEncodingError();

    // vsnprintf returns >0 and <n on success.
    // This is sadly a super generic error.
    if (rc >= size + 1)
        throw FormatWriteFault();

    va_end(args);
    append(buf.get());
}

void StringBuilder::prependf(const char* fmt, ...)
{
    // FIXME: Unhandled possible failures (might return 0, etc).
    va_list args;
    va_start(args, fmt);
    unsigned size = std::vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    va_start(args, fmt);
    auto buf = std::make_unique<char[]>(size + 1);
    std::vsnprintf(buf.get(), size + 1, fmt, args);
    va_end(args);
    prepend(buf.get());
}

String StringBuilder::build()
{
    if (m_built)
        throw StringBuilder_DoubleBuildNotAllowed();
    String s(std::move(chars()));
    m_built = true;
    return s;
}

StringBuilder& StringBuilder::operator=(const StringBuilder& builder)
{
    //m_chars = std::make_unique<char[]>(builder.size() + 1);
    std::strcpy(chars(), builder.chars());
    //size() = builder.size();
    m_built = builder.m_built;
    return *this;
}
