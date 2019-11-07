#ifndef CORE_H
#define CORE_H

template<typename _T>
struct HexFormat
{
    template<typename _ArgT>
    constexpr explicit HexFormat(const _ArgT& t) : data(t)
    {
    }
    const _T data;
};

#include <cstdio>
#include <cstdlib>
#define FATAL_ERROR_IF(x, msg)                                                           \
    if (x)                                                                               \
    {                                                                                    \
        fprintf(stderr, "FATAL ERROR: %s: %s\n", __PRETTY_FUNCTION__, msg);              \
        abort();                                                                         \
    }

#define DEBUGMODE 1
#if DEBUGMODE
#define ASSERT(cond) _assert((cond), __FILE__, __PRETTY_FUNCTION__, __LINE__, #cond)

inline void _assert(bool result, const char* file, const char* function, unsigned line,
                    const char* condition_str)
{
    if (!result)
    {
        fprintf(stderr,
                "(( ASSERTION FAILED at %s:%u in `%s`. Failed condition: `%s`. ))\n",
                file, line, function, condition_str);
        abort();
    }
}

#include <cctype>
#include <cstring>

inline void _print_memory(const char* from, const char* to, const char* what = "???",
                          std::size_t additional_bytes = 2)
{
    char* current = const_cast<char*>(from) - additional_bytes;
    char* internal_to = const_cast<char*>(to) + additional_bytes;

    printf("\nMEMORY DUMP FROM %p TO %p [SIZE=0x%x] (%s)\n", static_cast<void*>(current),
           static_cast<void*>(internal_to), unsigned(to - from), what);

    printf("POS  ");

    for (int i = -int(additional_bytes); i < to - from + int(additional_bytes); ++i)
    {
        printf("%3x ", i < 0 ? -i : i);
    }

    printf("\nHEX  ");

    for (; current < internal_to; ++current)
    {
        printf("%3x ", *current);
    }

    printf("\nCHR  ");

    // reset current ptr
    current = const_cast<char*>(from) - additional_bytes;
    for (; current < internal_to; ++current)
    {
        if (isprint(*current))
            printf("'%c' ", *current);
        else if (*current == 0)
            printf("NUL ");
        else
            printf("??? ");
    }

    printf("\nDAT  ");


    if (from == to)
    {
        for (std::size_t i = additional_bytes; i > 0; --i)
        {
            printf("    ");
        }
        printf("  ^ [S=0]");
    }
    else
    {
        for (int i = -int(additional_bytes); &from[i] < to; ++i)
        {
            if (i < 0)
                printf("%3c ", ' ');
            else
                printf("%3c ", '^');
        }
    }

    printf("\n\n");
}

inline void _print_memory(const char* from, std::size_t size, const char* what = "???",
                          std::size_t additional_bytes = 2)
{
    _print_memory(from, from + size, what, additional_bytes);
}

#else

#define ASSERT(x)

template<typename... _Args>
inline constexpr void _print_memory(_Args&&...)
{
}
#endif

#endif // CORE_H
