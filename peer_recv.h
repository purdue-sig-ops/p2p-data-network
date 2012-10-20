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

void init_listener (int);

#ifdef	__cplusplus
}
#endif

#endif	/* PEER_RECV_H */

