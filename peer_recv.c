#include "peer_recv.h"

//network headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

//threading headers
#include <pthread.h>
#include <semaphore.h>

//standard library headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//custom libraries used
#include "util/list.h"

static tcp_handler handler;

static void * event_wrapper (void *);

/*
 * This function sets up a socket for listening on the specified TCP port. It
 * hides the details of multi-threading and socket handling so that the protocol
 * code only has to worry about the protocol itself.
 */
void init_listener (char * port, tcp_handler handle)
{
    struct addrinfo hints, * serv, * ptr;
    struct sockaddr incoming;
    pthread_t handlers[THREADCOUNT];
    lock_list slave_list;
    
    int master, slave, s_queue[QUEUELEN];
    int addr_len = sizeof(incoming);
    int status, i;
    
    //initialize the socket queue and thread pool
    llist_init(& slave_list);
    handler = handle;
    for (i = 0; i < THREADCOUNT; i++)
        pthread_create(&handlers[i], NULL, event_wrapper, & slave_list);
    
    //setup the hints for getaddrinfo
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;        //don't care about IP version
    hints.ai_socktype = SOCK_STREAM;    //TCP
    hints.ai_flags = AI_PASSIVE;        //do things for me
    
    status = getaddrinfo(NULL, port, &hints, &serv);
    if (status != 0)
    {
        perror("Failed to get local address information.\n");
        exit(1);
    }
    
    // go through the list of IP's until we can bind to one
    for (ptr = serv; ptr != NULL; ptr = ptr->ai_next)
    {
        master = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (master < 0)
        {
            perror("Failed to create a socket.\n");
            continue;
        }
        
        status = bind(master, ptr->ai_addr, ptr->ai_addrlen);
        // exit loop once we have a successful bind
        if (status == 0)
            break;
        
        close(master);     //if it didn't bind...
    }
    
    if (status != 0)
    {
        perror("Failed to bind the socket to an IP address.\n");
        exit(1);
    }
    
    status = listen(master, 8);
    if (status != 0)
    {
        perror("I have no fucking idea...\n");
        exit(1);
    }
    
    while (slave = accept(master, &incoming, &addr_len))
    {
        //integers are normally the same size as a pointer
        intptr_t temp = slave;
        
        pthread_mutex_lock(& slave_list.mutex);
        
        push_first(& slave_list.lst, (void *)temp);
        
        pthread_mutex_unlock(& slave_list.mutex);
        sem_post(& slave_list.control); //signal handler threads
    }
}

/*
 * This function wraps the TCP handler call so that it need only concern itself
 * with socket I/O. It's somewhat similar to an event handler, using semaphores
 * as event triggers.
 */
static void * event_wrapper (void * arg)
{
    lock_list * lst = arg;
    intptr_t value;
    int sock_fd, status;
    
    while (1)
    {
        sem_wait(& lst->control); //consume input
        pthread_mutex_lock(& lst->mutex);
        
        value = (intptr_t)pop_last(& lst->lst);
        sock_fd = value;
        
        pthread_mutex_unlock(& lst->mutex);
        
        handler(sock_fd);
        close(sock_fd);     //just in case the TCP handler doesn't
    }
}
