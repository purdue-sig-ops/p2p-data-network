#include <string.h>
#include <stdlib.h>
//#include <openssl/sha.h>
#include "id.h"


void id_init(id * ident, const char * data)
{
	memcpy(ident->data, data, M / 8);
}

void id_alloc_hash(id * ident, const unsigned char * d, unsigned long n)
{
	//TODO: Implement
}

void id_copy(id * dest, id * src)
{
    memcpy(dest->data, src->data, M / 8);
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

//algorithm copied from ID.java in open-chord_1.0.5
//open-chord.sourceforge.net
void id_add_p2(id * dest, id * src, int p)
{
	int index_of_byte = (M / 8) - 1 - (p / 8);
	char to_add[] = {1,2,4,8,16,32,64,-128};
	char value_to_add = to_add[p % 8];
	char old_value;
	if(p >= 0 && p < M)
	{
		memcpy(dest->data, src->data, M / 8);
		do
		{
			old_value = dest->data[index_of_byte];
			dest->data[index_of_byte] += value_to_add;
			value_to_add = 1;
		}
		while(old_value < 0 && dest->data[index_of_byte] >= 0 && index_of_byte-- > 0);
	}
}
