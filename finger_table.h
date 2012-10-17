#ifndef FINGER_TABLE_H
#define FINGER_H

#include "node.h"
#include "id.h"

typedef struct
{
	id * my_id;
	node * * nodes;
} finger_table;

finger_table * finger_table_alloc(id * my_id);
void finger_table_free(finger_table * t);
id * finger_table_start(finger_table * t, int i);
int finger_table_interval(finger_table * t, int i, id * value);
node * finger_table_node(finger_table * t, int i);
void finger_table_set_node(finger_table * t, int i, node * n);

#endif
