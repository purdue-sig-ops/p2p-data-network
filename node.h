#ifndef NODE_H
#define NODE_H

#include<inttypes.h>

#include "id.h"

typedef struct
{
	//id of node
	id * ident;
	//ip address of node
	int32_t ip;
} node;

//Allocate a node with the ip address
node * node_alloc(int32_t ip);
//Free a node
void node_free(node * n);
//Get the id of the node
id * node_get_id(node * n);
//Get the ip address of the node
int32_t node_get_ip(node * n);
#endif
