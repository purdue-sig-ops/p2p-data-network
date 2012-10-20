#include <stdlib.h>

#include "../list.h"

void * pop_last (list * lst)
{
    struct dl_node * node = lst->tail;
    void * data = 0;
    
    if (node != 0)
    {
        data = node->data;
        lst->tail = node->prev;
        free(node);
        
        if (lst->tail == 0)
        {
            lst->head = 0;
        }
        else
        {
            lst->tail->next = 0;
        }
    }
    
    return data;
}
