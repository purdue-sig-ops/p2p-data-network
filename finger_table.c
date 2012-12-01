#include "finger_table.h"
#include <stdlib.h>

//init the finger table
void ft_init(finger_table * t, id * my_id)
{
	id_copy(&t->my_id, my_id);
}

void ft_free(finger_table * t)
{
	//free the finger table
	int i;
	for(i = 0; i < M; ++i)
	{
		if(t->nodes[i] != NULL)
			node_free(t->nodes[i]);
	}
}

//The start operation as defined in the Chord Paper
int ft_start(finger_table * t,id * dst, int i)
{
	//if the index is valid, return the id + power of 2 needed
	if(i > 0 && i <= M)
	{
		id_add_p2(dst, &t->my_id, i - 1);
		return 0;
	}
	//otherwise, fail
	else
		return -1;
}

//Check if a id is in the interval of this finger as defined in the Chord paper
int ft_interval(finger_table * t, int i, id * value)
{
	id low,high;
	//if the index is valid
	if(i > 0 && i <= M)
	{
		//get the bounds of the interval
		ft_start(t, &low, i);
		ft_start(t, &high, (i + 1) % M);
        //if high < low (interval wraps around circle), checks are diff
        switch(id_compare(&high, &low))
        {
            case 1:
                return id_compare(&low, value) <= 0 && id_compare(&high, value) == 1;
            case -1:
                return id_compare(&low, value) <= 0 || id_compare(&high, value) == 1;
            case 0:
                return 0;
        }
    }
}


//look up the actual finger node = node operation as defined in Chord paper
node * ft_get(finger_table * t, int i)
{
	if(i > 0 && i <= M)
		return t->nodes[i];
	else
		return NULL;
}
//set the finger node
void ft_set(finger_table * t,int i, node * n)
{
	if(i > 0 && i <= M)
		t->nodes[i] = n;
}
