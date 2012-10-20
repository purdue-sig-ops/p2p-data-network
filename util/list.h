#ifndef LIST_H
#define	LIST_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <pthread.h>
#include <semaphore.h>

    struct dl_node
    {
        union dl_data * data;
        struct dl_node * next, * prev; 
    };
    
    typedef struct 
    {
        struct dl_node * head, * tail;
        int length;
    } list;
    
    typedef struct
    {
        list lst;
        sem_t control;
        pthread_mutex_t mutex;
    } lock_list;
    
    void list_init (list *);
    void llist_init (lock_list *);
    void push_first (list *, void *);
    void push_last (list *, void *);
    void * pop_first (list *);
    void * pop_last (list *);

#ifdef	__cplusplus
}
#endif

#endif	/* LIST_H */

