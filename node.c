#include "node.h"
#include <stdlib.h>

node * node_alloc(const char* ip)
{
	//allocate the node
	node * n = malloc(sizeof(node));
	//TODO: parse the ip and fill the node
	return n;
}

void node_free(node * n)
{
	//free the id and then the struct
	id_free(n->ident);
	free(n->ip);
	free(n);
}

id * node_get_id(node * n)
{
	return n->ident;
}

struct sockaddr * node_get_ip(node * n)
{
	return n->ip;
}
