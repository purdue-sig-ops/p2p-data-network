#include <stdlib.h>

#include "../list.h"

void * pop_first (list * lst)
{
    struct dl_node * node = lst->head;
    void * data = 0;
    
    if (node != 0)
    {
        data = node->data;
        lst->head = node->next;
        free(node);
        
        if (lst->head == 0)
        {
            lst->tail = 0;
        }
        else
        {
            lst->head->prev = 0;
        }
    }
    
    return data;
}