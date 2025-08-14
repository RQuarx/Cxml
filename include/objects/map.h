#pragma once
#ifndef __OBJECTS__MAP_H
#define __OBJECTS__MAP_H
#include <stddef.h>

constexpr float MAP_LOAD_FACTOR   = 0.75F;
constexpr float MAP_GROWTH_FACTOR = 1.5F;


struct pair
{
    char *key;
    char *value;
};


[[nodiscard, gnu::returns_nonnull, gnu::nonnull(1)]]
struct pair *pair_new( const char *restrict p_key,
                       const char *restrict p_value );


[[gnu::nonnull(1)]]
void pair_delete( struct pair *restrict p_pair );


#define PAIR( p_ptr ) \
    ((struct pair *)p_ptr)


struct map
{
    size_t alloc_size;
    size_t pair_amount;
    struct list **buckets;
};


[[nodiscard, gnu::returns_nonnull]]
struct map *map_new( size_t p_initial_size );


[[gnu::nonnull(1, 2)]]
void map_add( struct map *restrict p_map,
              const char *restrict p_key,
              const char *restrict p_value );


[[gnu::nonnull(1)]]
void map_resize( struct map *restrict p_map, size_t p_new_size );


[[nodiscard, gnu::nonnull(1, 2)]]
const char *map_get( const struct map *restrict p_map,
                     const char       *restrict p_key );


[[gnu::nonnull(1)]]
void map_delete( struct map *restrict p_map );


#endif /* __OBJECTS__MAP_H */
