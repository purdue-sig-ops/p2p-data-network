#include "node.h"
#include <stdlib.h>

node * node_alloc(int32_t ip)
{
	//allocate the node
	node * n = malloc(sizeof(node));
	//n->id = id_alloc(sha1(ip));
	n->ip = ip;
	return n;
}

void node_free(node * n)
{
	//free the id and then the struct
	id_free(n->ident);
	free(n);
}

id * node_get_id(node * n)
{
	return n->ident;
}

int32_t node_get_ip(node * n)
{
	return n->ip;
}
