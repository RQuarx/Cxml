#include <stdlib.h>
#include <string.h>

#include "objects/list.h"
#include "objects/map.h"
#include "print.h"
#include "utils.h"

#define STRDUP_OR_NULL( p_str ) \
    p_str == nullptr ? nullptr : strdup(p_str)


struct pair *
pair_new( const char *restrict p_key,
          const char *restrict p_value )
{
    struct pair *new = xmalloc(sizeof(struct pair));
    new->key   = strdup(p_key);
    new->value = STRDUP_OR_NULL(p_value);
    return new;
}


void
pair_delete( struct pair *restrict p_pair )
{
    if (p_pair->value != nullptr) free(p_pair->value);
    if (p_pair->key   != nullptr) free(p_pair->key);
    free(p_pair);
}


[[nodiscard, gnu::nonnull(1)]]
static size_t
map_hash( const char *restrict p_str )
{
    /* djb2 hash algorithm */
    size_t hash = 5381;
    char c;

    while ((c = *p_str++))
        /* hash * 33 + c */
        hash = ((hash << 5) + hash) + c;

    return hash;
}


[[gnu::nonnull(1, 2)]]
static void
map_insert_pair( struct map  *restrict p_map,
                 struct pair *restrict p_pair )
{
    size_t idx = map_hash(p_pair->key) % p_map->alloc_size;
    struct list *new = list_new(p_pair);
    list_prepend(&p_map->buckets[idx], new);
    p_map->pair_amount++;
}


struct map *
map_new( size_t p_initial_size )
{
    struct map *map = xmalloc(sizeof(struct map));

    map->alloc_size = p_initial_size;
    map->pair_amount = 0;

    if (map->alloc_size != 0)
        map->buckets = xmalloc(sizeof(struct list *) * map->alloc_size);

    println_dbg("Created a new map with a size of %zu", p_initial_size);
    return map;
}


void
map_resize( struct map *restrict p_map, size_t p_new_size )
{
    struct list **old_buckets = p_map->buckets;
    size_t old_size = p_map->alloc_size;

    p_map->buckets = xmalloc(sizeof(struct list *) * p_new_size);
    p_map->alloc_size = p_new_size;
    p_map->pair_amount = 0;

    for (size_t i = 0; i < old_size; i++) {
        LIST_FOREACH(old_buckets[i],
            map_insert_pair(p_map, curr->data);
        );
    }

    free(old_buckets);
    println_dbg("Resizing map from %zu to %zu", old_size, p_new_size);
}


void
map_add( struct map *restrict p_map,
         const char *restrict p_key,
         const char *restrict p_value )
{
    size_t idx = map_hash(p_key) % p_map->alloc_size;
    LIST_FOREACH(p_map->buckets[idx],
        if (strcmp(PAIR(curr->data)->key, p_key) != 0) continue;
        PAIR(curr->data)->value = STRDUP_OR_NULL(p_value);
    );

    struct pair *new_pair = pair_new(p_key, p_value);
    map_insert_pair(p_map, new_pair);

    if ((float)p_map->pair_amount / p_map->alloc_size > MAP_LOAD_FACTOR)
        map_resize(p_map, p_map->alloc_size * MAP_GROWTH_FACTOR);
    println_dbg("Added [%s, %s] to map", p_key, p_value);
}


const char *
map_get( const struct map *restrict p_map,
         const char       *restrict p_key )
{
    size_t idx = map_hash(p_key) % p_map->alloc_size;

    LIST_FOREACH(p_map->buckets[idx],
        if (strcmp(p_key, PAIR(curr->data)->key) == 0)
            return PAIR(curr->data)->value;
    );
    return nullptr;
}


static void
list_pair_delete( void *p_pair )
{ pair_delete(p_pair); }


void
map_delete( struct map *restrict p_map )
{
    for (size_t i = 0; i < p_map->alloc_size; i++) {
        list_delete_func(p_map->buckets[i], list_pair_delete);
    }

    free(p_map->buckets);
    free(p_map);
    println_dbg("Deleting a map");
}
