#pragma once
#ifndef __PRINT_H
#define __PRINT_H
#include <ctype.h>
#include <stdio.h>


[[gnu::format(printf, 2, 3), gnu::nonnull(1, 2)]]
void fprint( FILE *restrict p_stream, const char *restrict p_fmt, ... );


[[gnu::format(printf, 2, 3), gnu::nonnull(1, 2)]]
void fprintln( FILE *restrict p_stream, const char *restrict p_fmt, ... );


[[gnu::format(printf, 1, 2), gnu::nonnull(1)]]
void print( const char *restrict p_fmt, ... );


[[gnu::format(printf, 1, 2), gnu::nonnull(1)]]
void println( const char *restrict p_fmt, ... );


[[gnu::format(printf, 1, 2), gnu::nonnull(1)]]
void println_dbg( const char *restrict p_fmt, ... );


[[maybe_unused, nodiscard]]
static const char *
remove_first_word( const char *p_sentence )
{
    while (*p_sentence && !isspace(*p_sentence))
        p_sentence++;
    while (*p_sentence &&  isspace(*p_sentence))
        p_sentence++;
    return p_sentence;
}





#endif /* __PRINT_H */
