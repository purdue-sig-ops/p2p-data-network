#include "../list.h"

#include <string.h>

void list_init (list * lst)
{
    memset(lst, 0, sizeof(list));
}