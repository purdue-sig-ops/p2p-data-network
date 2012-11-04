#include <socket.h>

#ifndef PEER_SEND_H
#define PEER_SEND_H

void init_send (int);
int send_to (struct in_addr *, char *, int);
int open (struct addrinfo *);

#endif
