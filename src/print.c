#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <sys/time.h>

#include "print.h"
#include "utils.h"

#define VFPRINT( p_stream, p_fmt )     \
    do {                               \
        va_list ap;                    \
        va_start(ap, p_fmt);           \
        vfprintf(p_stream, p_fmt, ap); \
        va_end(ap);                    \
    } while (0)


static void
print_time( FILE *restrict p_stream )
{
    struct timeval now;
    gettimeofday(&now, nullptr);

    struct tm tm_local;
    if (localtime_r(&now.tv_sec, &tm_local) == nullptr)
        ERR("localtime_r failed: %s", strerror(errno));

    int32_t min = tm_local.tm_min;
    int32_t sec = tm_local.tm_sec;
    int32_t mil = now.tv_usec / 1000;
    fprint(p_stream, "%d:%02d.%03d", min, sec, mil);
}


void
fprint( FILE *restrict p_stream, const char *restrict p_fmt, ... )
{ VFPRINT(p_stream, p_fmt); }


void
fprintln( FILE *restrict p_stream, const char *restrict p_fmt, ... )
{
    VFPRINT(p_stream, p_fmt);
    putc('\n', p_stream);
}


void
print( const char *restrict p_fmt, ... )
{ VFPRINT(stdout, p_fmt); }


void
println( const char *restrict p_fmt, ... )
{
    VFPRINT(stdout, p_fmt);
    putc('\n', stdout);
}


void
println_dbg( const char *restrict p_fmt, ... )
{
    const char *debug_mode = getenv("CXML_DEBUG");
    if (debug_mode == nullptr) return;

    if (strncmp("true", debug_mode, 4) == 0) {
        print_time(stderr);
        VFPRINT(stderr, " [DEBUG]: ");
        VFPRINT(stderr, p_fmt);
        putc('\n', stderr);
    }
}
