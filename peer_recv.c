#include "peer_recv.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void _init_listener (char *);

void init_listener (int port)
{
    //can be allocated on stack...only used beneath this stack frame
    char port_str[8];
    sprintf(port_str, "%d", port);
    printf("%s\n", port_str);
    
    _init_listener(port_str);
}

static void _init_listener (char * port)
{
    struct addrinfo hints, * serv, * ptr;
    struct sockaddr incoming;
    char buffer[512];
    
    char * ipv;
    void * addr;
    int master, slave;
    
    int status, len;
    len = sizeof(incoming);
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;        //deal with ip version for me
    hints.ai_socktype = SOCK_STREAM;    //TCP
    hints.ai_flags = AI_PASSIVE;        //do things for me
    
    status = getaddrinfo(NULL, port, &hints, &serv);
    //getaddrinfo returns non-zero value on error
    if (status != 0)
    {
        perror("Failed to get local address information.\n");
        exit(1);
    }
    
    for (ptr = serv; ptr != NULL; ptr = ptr->ai_next)
    {
        master = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (master < 0)
        {
            perror("Failed to create a socket.\n");
            continue;
        }
        
        status = bind(master, ptr->ai_addr, ptr->ai_addrlen);
        if (status == 0)
        {
            break;
        }
        
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
    
    while (slave = accept(master, &incoming, &len))
    {
    	read(slave, buffer, 512);
    	printf("%s\n", buffer);
    }
}
