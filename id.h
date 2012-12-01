#ifndef ID_H
#define ID_H

#include <inttypes.h>

#define M 160

typedef struct
{
	//M Bit Identifier
	char data[M / 8];
} id;

//Init
void id_init(id *, const char *);
void id_init_hash(id *, const unsigned char *, unsigned long);
//Copy a ID
void id_copy(id *, id *);
//Compare two IDs
int id_compare(id *, id *);
//Add p^2 to src
void id_add_p2(id *, id *, int);

#endif
