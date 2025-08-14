#include <stdlib.h>
#include "objects/list.h"
#include "utils.h"


struct list *
list_new( void *p_data )
{
    struct list *new = xmalloc(sizeof(struct list));
    new->data = p_data;
    new->next = nullptr;
    return new;
}


void
list_append( struct list *restrict p_list, struct list *restrict p_val )
{
    LIST_FOREACH(p_list,
        if (curr->next == nullptr) {
            curr->next = p_val;
            break;
        }
    );
}


void
list_prepend( struct list **restrict p_list, struct list *restrict p_val )
{
    p_val->next = *p_list;
    *p_list = p_val;
}


void
list_delete_func( struct list *restrict p_list,
                  list_func_delete_x    p_delete_func )
{
    LIST_FOREACH(p_list,
        p_delete_func(curr->data);
        free(curr);
    );
    free(p_list);
}
