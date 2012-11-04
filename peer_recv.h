#ifndef PEER_RECV_H
#define	PEER_RECV_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "util/list.h"
#include <semaphore.h>
#include <netdb.h>

#define BUFFLEN 512
#define RECV_FLAGS 0
#define QUEUELEN 16
#define THREADCOUNT 4


    typedef void (* tcp_handler) (int sock);
    void init_listener (char *, tcp_handler, struct addrinfo *);


#ifdef	__cplusplus
}
#endif

#endif	/* PEER_RECV_H */

