#ifndef PARSE_H
#define PARSE_H

#include "id.h"

typedef struct
{
	int code;
	id * ident;
	char * addr;
} message;

message * parse_message(const char * buffer);
void message_free(message * msg);
#endif
