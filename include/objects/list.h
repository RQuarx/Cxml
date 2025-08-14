#pragma once
#ifndef __OBJECTS__LIST_H
#define __OBJECTS__LIST_H


/* Singly linked list node */
struct list
{
    void *data;
    struct list *next;
};


/**
 * Create a new list node containing P_DATA,
 * P_DATA must not be freed outside the node.
 */
[[nodiscard, gnu::returns_nonnull, gnu::nonnull(1)]]
struct list *list_new( void *p_data );


/**
 * Appends P_VAL to the end of P_LIST.
 */
[[gnu::nonnull(1, 2)]]
void list_append( struct list *restrict p_list,
                  struct list *restrict p_val );


/**
 * Prepends P_VAL to P_LIST.
 */
[[gnu::nonnull(1, 2)]]
void list_prepend( struct list **restrict p_list,
                   struct list  *restrict p_val );


/**
 * Deletes all nodes in P_LIST, calling P_DELETE_FUNC on each data.
 */
typedef void (list_func_delete_x)( void * );
[[gnu::nonnull(1, 2)]]
void list_delete_func( struct list *restrict p_list,
                       list_func_delete_x    p_delete_func );


/**
 * Iterate through P_LIST, P_BODY may use `curr` to refer to the current node.
 */
#define LIST_FOREACH( p_list, p_body )                                         \
    do {                                                                       \
        for (struct list *curr = p_list; curr != nullptr; curr = curr->next) { \
            p_body;                                                            \
        }                                                                      \
    } while (0)


#endif /* __OBJECTS__LIST_H */
