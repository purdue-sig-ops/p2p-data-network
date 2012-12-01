#ifndef PARSE_H
#define PARSE_H

#include "id.h"

typedef struct
{
	int code;
	id ident;
	char * addr;
} msg;

void parse_msg(msg *, const char *);
void msg_free(msg *);
#endif
