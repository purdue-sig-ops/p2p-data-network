#include "finger_table.h"
#include <stdlib.h>

finger_table * finger_table_alloc(id * my_id)
{
	//allocate the finger table
	int i;
	finger_table * t = malloc(sizeof(finger_table));
	t->my_id = id_copy(my_id);
	t->nodes = malloc(sizeof(node*) * M);
	for(i = 0; i < M; ++i)
	{
		t->nodes[i] = NULL;
	}
	return t;
}

void finger_table_free(finger_table * t)
{
	//free the finger table
	int i;
	for(i = 0; i < M; ++i)
	{
		if(t->nodes[i] != NULL)
			node_free(t->nodes[i]);
	}
	free(t->nodes);
	id_free(t->my_id);
	free(t);
}

//The start operation as defined in the Chord Paper
id * finger_table_start(finger_table * t, int i)
{
	//if the index is valid, return the id + power of 2 needed
	if(i > 0 && i <= M)
	{
		return id_add_p2(t->my_id, i - 1);
	}
	//otherwise, fail
	else
		return NULL;
}

//Check if a id is in the interval of this finger as defined in the Chord paper
int finger_table_interval(finger_table * t, int i, id * value)
{
	id * low, * high;
	//if the index is valid
	if(i > 0 && i <= M)
	{
		//get the bounds of the interval
		low = finger_table_start(t, i);
		high = finger_table_start(t, (i + 1) % M);
        //if high < low (interval wraps around circle), checks are diff
        switch(id_compare(high, low))
        {
            case 1:
                return id_compare(low, value) <= 0 && id_compare(high, value) == 1;
            case -1:
                return id_compare(low, value) <= 0 || id_compare(high, value) == 1;
            default:
                return 0;
        }
    }
}

//set the finger node
void finger_table_set_node(finger_table * t,int i, node * n)
{
	if(i > 0 && i <= M)
		t->nodes[i] = n;
}

//look up the actual finger node - node operation as defined in Chord paper
node * finger_table_node(finger_table * t, int i)
{
	if(i > 0 && i <= M)
		return t->nodes[i];
	else
		return NULL;
}
