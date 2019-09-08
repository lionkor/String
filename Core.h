#ifndef CORE_H
#define CORE_H

#define ASSERT(cond) _assert((cond), __FILE__, __PRETTY_FUNCTION__, __LINE__, #cond)

#include <cstdio>
inline void _assert (bool result, const char* file, const char* function, unsigned line, const char* condition_str)
{
    if (!result) fprintf (stderr, "(( ASSERTION FAILED at %s:%u in `%s`. Failed condition: `%s`. ))\n", file, line, function, condition_str);
}

#endif // CORE_H
