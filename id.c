#include <string.h>
#include <stdlib.h>
#include "id.h"

id * id_alloc(int8_t * data)
{
	//allocate space for the id
	id * ident = malloc(sizeof(id));
	ident->data = malloc(M / 8);
	memcpy(ident->data, data, M / 8);
	return ident; 
}

void id_free(id * ident)
{
	//free the actual id, then the id struct
	free(ident->data);
	free(ident);
}

id * id_copy(id * org)
{
	//just allocate a new id with our identifier
	return id_alloc(org->data);
}

//algorithm copied from ID.java in open-chord_1.0.5
//open-chord.sourceforge.net
int id_compare(id * l, id * r)
{
	int i;
	for(i = 0; i < M / 8; ++i)
	{
		if(l->data[i] < r->data[i])
			return -1;
		else
		{
			if(l->data[i] > r->data[i])
				return 1;
		}
	}
	return 0;
}

//algorithm copied from ID.java in open-chord_1.0.5
//open-chord.sourceforge.net
id * id_add_p2(id * ident, int p)
{
	int index_of_byte = (M / 8) - 1 - (p / 8);
	int8_t to_add[] = {1,2,4,8,16,32,64,-128};
	int8_t value_to_add = to_add[p % 8];
	int8_t old_value;
	int8_t * copy;
	id * ret;
	if(p > 0 && p < M)
	{
		copy = malloc(M / 8);
		memcpy(copy, ident->data, M / 8);
		do
		{
			old_value = copy[index_of_byte];
			copy[index_of_byte] += value_to_add;
			value_to_add = 1;
		}
		while(old_value < 0 && copy[index_of_byte] >= 0 && index_of_byte-- > 0);
		ret = id_alloc(copy);
		free(copy);
		return ret;
	}
	else
		return NULL;
}
