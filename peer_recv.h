/*
 * File:   peer_recv.h
 * Author: caleb
 *
 * Created on September 22, 2012, 6:21 AM
 */

#ifndef PEER_RECV_H
#define	PEER_RECV_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <netinet/in.h>

#define BUFFLEN 128
#define RECV_FLAGS 0

typedef int (* udp_handler)(char *, int, struct sockaddr_in *, int);
int init_udp (int);
void add_handler (udp_handler);

#ifdef	__cplusplus
}
#endif

#endif	/* PEER_RECV_H */

