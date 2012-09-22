

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <netdb.h>

#include <netinet/in.h> 
#include <arpa/inet.h>


#define BUFFLEN 512
#define RECV_FLAGS 0
int init_send (int port)
{
    struct sockaddr_in sin, recv;
    int sock_fd, rlen, recv_len;
    //initialize an input buffer
    char * buf = (char *)malloc(BUFFLEN * sizeof(char));
    if (buf == 0) 
        error("Buffer failed to initialize.");
    
    rlen = sizeof(recv);
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (sock_fd < 0)
        error("Socket failed to initialize.");
    
    memset((char *) &sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    

    
    while (1)
    {
        recv_len = (int)sendto(sock_fd, buf, BUFFLEN, RECV_FLAGS, &recv, rlen);  
        if (recv_len < 0)
            error("Function recvfrom() failed.");
        printf("Received packet.");
    }
    
    return 1;
}
