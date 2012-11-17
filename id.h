#ifndef ID_H
#define ID_H

#include <inttypes.h>

#define M 160

typedef struct
{
	//M Bit Identifier
	char * data;
} id;

//Allocate a ID
id * id_alloc(const char * data);
id * id_alloc_hash(const unsigned char * d, unsigned long n);
//Free a ID
void id_free(id * ident);
//Copy a ID
id * id_copy(id * ident);
//Compare two IDs
int id_compare(id * l, id * r);
//Get an ID that is equal to (ident + 2^p)
id * id_add_p2(id * ident, int p);

#endif
