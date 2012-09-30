

#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define SEND_FLAGS 0
#define SOCK_FLAGS 0

static struct sockaddr_in addr;
static int sock_fd, addr_len;

int init_send (int port)
{
    addr_len = sizeof(addr);
    sock_fd = socket(AF_INET, SOCK_DGRAM, SOCK_FLAGS);

    if (sock_fd < 0)
        error("Socket failed to initialize.");

    memset((char *) &addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
}

int send_to (struct in_addr * ip, char * buffer, int buffer_len)
{
	int send_length;
	addr.sin_addr = *ip;

	send_length = sendto(sock_fd, buffer, buffer_len, SEND_FLAGS, (struct sockaddr *)&addr, addr_len);
	memset((char *)&(addr.sin_addr), 0, sizeof(struct in_addr));

	return send_length;
}
