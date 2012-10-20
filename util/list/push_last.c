#include <stdlib.h>

#include "../list.h"

void push_last (list * lst, void * data)
{
    struct dl_node * node = (struct dl_node *)calloc(1, sizeof(struct dl_node));
    node->data = data;
    
    node->prev = lst->tail;
    if (lst->tail != 0)
    {
        lst->tail->next = node;
    }
    else
    {
        lst->head = node;
    }
    
    lst->tail = node;
    lst->length ++;
}