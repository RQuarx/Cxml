#pragma once
#ifndef __UTILS_H
#define __UTILS_H
#include <stddef.h>
#include <stdio.h>


[[gnu::malloc, gnu::alloc_size(1, 1), nodiscard, gnu::returns_nonnull]]
void *xmalloc( size_t p_size_byte );


/**
 * Removes a range of a string, starting at p_start,
 * and ending at p_start + p_len.
 */
[[nodiscard, gnu::nonnull(1), gnu::malloc]]
char *strrm( const char *restrict p_str, size_t p_start, size_t p_len );


/**
 * Returns the first occurance of @p p_char in @p p_str .
 */
[[nodiscard, gnu::nonnull(1)]]
size_t strchrs( const char *restrict p_str, char p_char );


#define ERR( p_fmt, ... )                                              \
    {                                                                  \
        char *func = strrm(__PRETTY_FUNCTION__, 0,                     \
                           strchrs(__PRETTY_FUNCTION__, ' ') + 1);     \
        fprintf(stderr, "\033[1;31mERROR\033[0;0m at %s in %s:%d\n",   \
                func, __FILE__, __LINE__);                             \
        fprintf(stderr, "  what(): " p_fmt __VA_OPT__(,) __VA_ARGS__); \
        putc('\n', stderr);                                            \
        abort();                                                       \
    }

#endif /* __UTILS_H */
