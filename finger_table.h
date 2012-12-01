#ifndef FINGER_TABLE_H
#define FINGER_H

#include "node.h"
#include "id.h"

typedef struct
{
	id my_id;
	node * nodes[M];
} finger_table;

void ft_init(finger_table * t, id * ident);
void ft_free(finger_table * t);
int ft_start(finger_table *,id*, int i);
int ft_interval(finger_table * t, int i, id * value);
node * ft_get(finger_table * t, int i);
void ft_set(finger_table * t, int i, node * n);

#endif
