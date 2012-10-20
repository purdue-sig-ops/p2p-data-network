#include "../list.h"

//threading headers
#include <pthread.h>
#include <semaphore.h>

#include <string.h>

void llist_init (lock_list * lst)
{
    list_init(& lst->lst);
    sem_init(& lst->control, 0, 0);
    
    pthread_mutex_init(& lst->mutex, NULL);
}