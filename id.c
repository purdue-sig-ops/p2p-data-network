#include <string.h>
#include <stdlib.h>
//#include <openssl/sha.h>
#include "id.h"

id * id_alloc(const char * data)
{
	//allocate space for the id
	id * ident = (id*)malloc(sizeof(id));
	ident->data = (char*)malloc(M / 8);
	memcpy(ident->data, data, M / 8);
	return ident;
}

id * id_alloc_hash(const unsigned char * d, unsigned long n)
{
/*
	id * ident = (id*)malloc(sizeof(id));
	ident->data = (char*)malloc(M / 8);
	SHA1(d, n, (unsigned char*)ident->data);
	return ident;
*/
	return NULL;
}

id * id_copy(id * ident)
{
    //copy ident and return it
    id * cpy = malloc(sizeof(id));
    cpy->data = malloc(M / 8);
    memcpy(cpy->data, ident->data, M / 8);
    return cpy;
}

void id_free(id * ident)
{
	//free the actual id, then the id struct
	free(ident->data);
	free(ident);
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

//helper function to directly get an id with data specified in the parameter - no copying
static id * id_load(char * data)
{
    id * ret = malloc(sizeof(id));
    ret->data = data;
    return ret;
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
	if(p >= 0 && p < M)
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
		return id_load(copy);
	}
	else
		return NULL;
}
