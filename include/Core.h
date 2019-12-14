#ifndef CORE_H
#define CORE_H

template<typename _T>
struct HexFormat
{
    constexpr explicit HexFormat(const _T& t) : data(t) {}

    template<typename _ArgT>
    constexpr explicit HexFormat(const _ArgT& t) : data(t)
    {
    }

    const _T data;
};
template<class _T>
explicit HexFormat(const _T& t)->HexFormat<_T>;

template<typename _T>
struct OctalFormat
{
    constexpr explicit OctalFormat(const _T& t) : data(t) {}

    template<typename _ArgT>
    constexpr explicit OctalFormat(const _ArgT& t) : data(t)
    {
    }
    const _T data;
};
template<class _T>
explicit OctalFormat(const _T& t)->OctalFormat<_T>;

struct PointerFormat
{
    template<typename _ArgT>
    constexpr explicit PointerFormat(const _ArgT* t)
        : data(reinterpret_cast<const void*>(t))
    {
    }
    const void* data;
};

template<typename _T>
struct PrecisionFormat
{
    constexpr explicit PrecisionFormat(const _T& t, unsigned size) : data(t), size(size)
    {
    }

    template<typename _ArgT>
    constexpr explicit PrecisionFormat(const _ArgT& t, unsigned size)
        : data(t), size(size)
    {
    }
    const _T       data;
    const unsigned size;
};
template<class _T>
explicit PrecisionFormat(const _T& t, unsigned s)->PrecisionFormat<_T>;


#include <cstdio>
#include <cstdlib>
#ifndef FATAL_ERROR_IF
#define FATAL_ERROR_IF(x, msg)                                                           \
    if (x)                                                                               \
    {                                                                                    \
        fprintf(stderr, "FATAL ERROR: %s: %s\n", __PRETTY_FUNCTION__, msg);              \
        abort();                                                                         \
    }
#endif // FATAL_ERROR_IF

#ifndef LOG
#define LOG(x) _log(__FILE__, __LINE__, __PRETTY_FUNCTION__, x, #x)
#endif // LOG

#include <iostream>
template<typename _T>
inline void _log(const char* file, unsigned long line, const char* function,
                 const _T& arg, const char* arg_name)
{
    fprintf(stdout, "LOG: %s:%lu (%s): %s = ", file, line, function, arg_name);
    std::cout << arg << std::endl;
}

#ifndef DEBUGMODE
#define DEBUGMODE 1
#endif // DEBUGMODE

#if DEBUGMODE

#ifndef ASSERT
#define ASSERT(cond) _assert((cond), __FILE__, __PRETTY_FUNCTION__, __LINE__, #cond)
#endif // ASSERT

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

template<typename _Ptr>
inline void _print_memory(_Ptr from_arg, _Ptr to_arg, const char* what = "no info",
                          std::size_t block_size = 16)
{
    char* from = static_cast<char*>((void*)from_arg);
    char* to   = static_cast<char*>((void*)to_arg);

    printf("\nMEMORY DUMP FROM %p TO %p [SIZE=0x%x] (%s)\n", static_cast<void*>(from),
           static_cast<void*>(to), unsigned(to - from), what);

    for (int i = -int(block_size); i < (to + block_size) - from; i += block_size)
    {
        printf("OFF  ");
        for (auto iter = from + i; iter != from + i + block_size; ++iter)
        {
            if (iter - from < 0)
                printf("-%0.3lx ", -(iter - from));
            else
                printf("%0.4lx ", iter - from);
        }
        printf("\n");

        printf("POS  ");
        for (auto iter = from + i; iter != from + i + block_size; ++iter)
        {
            printf("%0.4lx ", reinterpret_cast<unsigned long>(iter) & 0xFFFF);
        }
        printf("\n");

        printf("HEX  ");
        for (auto iter = from + i; iter != from + i + block_size; ++iter)
        {
            printf("%0.4x ", *(iter)&0xFFFF);
        }
        printf("\n");

        printf("CHR  ");
        for (auto iter = from + i; iter != from + i + block_size; ++iter)
        {
            if (isprint(*iter))
                printf(" '%c' ", *iter);
            else if (*iter == 0)
                printf("NULL ");
            else
                printf("???? ");
        }
        printf("\n");

        printf("DAT  ");

        for (auto iter = from + i; iter != from + i + block_size; ++iter)
        {
            if (iter == from)
                printf("[----");
            else if (iter == to - 1)
                printf("----]");
            else if (iter >= from && iter <= to - 1)
                printf("-----");
            else
                printf("     ");
        }

        // end of block
        printf("\n\n");
    }

    return;
}

#else

#ifndef ASSERT
#define ASSERT(x)
#endif // ASSERT

template<typename... _Args>
inline constexpr void _print_memory(_Args&&...)
{
}
#endif // FIXME what's this

#endif // CORE_H
