#include <stdlib.h>

#include "../list.h"

void push_first (list * lst, void * data)
{
    struct dl_node * node = (struct dl_node *)calloc(1, sizeof(struct dl_node));
    node->data = data;
    
    node->next = lst->head;
    if (lst->head != 0)
    {
        lst->head->prev = node;
    }
    else
    {
        lst->tail = node;
    }
    
    lst->head = node;
    lst->length ++;
}