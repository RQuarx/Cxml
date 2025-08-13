#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "utils.h"


void *
xmalloc( size_t p_size_byte )
{
    if (p_size_byte == 0)
        ERR("Tried to allocate a size 0 memory.");

    void *ptr = malloc(p_size_byte);
    if (ptr == nullptr)
        ERR("Failed to allocate %zu bytes: %s", p_size_byte, strerror(errno));

    return ptr;
}


char *
strrm( const char *restrict p_str, size_t p_start, size_t p_len )
{
    /* Full string length, minus the removed length. */
    const size_t buff_len = strlen(p_str) + 1 - p_len;
    size_t i = 0;
    char *buff = xmalloc(buff_len);

    while (i < p_start) {
        buff[i] = p_str[i];
        i++;
    }

    p_str += p_len;

    while (i < buff_len) {
        buff[i] = p_str[i];
        i++;
    }

    return buff;
}


size_t
strchrs( const char *restrict p_str, char p_char )
{
    size_t i = 0;
    for (; p_str[i] != '\0'; i++)
        if (p_str[i] == p_char) return i;

    return i;
}
