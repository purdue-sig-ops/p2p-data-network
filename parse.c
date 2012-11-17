#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

static message * message_alloc(int code, id * ident, char * addr)
{
	message * ret = (message*)malloc(sizeof(message));
	ret->code = code;
	ret->ident = ident;
	ret->addr = addr;
	return ret;
}

void message_free(message * msg)
{
	if(msg->ident != NULL)
		id_free(msg->ident);
	if(msg->addr != NULL)
		free(msg->addr);
	free(msg);
}

message * parse_message(const char * buffer)
{
	int code = -1;
	id * ident = NULL;
	char * addr = NULL;
	char * hash_buf = NULL;
	const char * fmt = NULL;
	message * _parse_message(const char * fmt)
	{
		addr = (char*)malloc(37 + 1);
		hash_buf = (char*)malloc(M/8 + 1);
		sscanf(buffer, fmt, hash_buf, addr);
		ident = id_alloc(hash_buf);
		free(hash_buf);
		return message_alloc(code, ident, addr);
	}
	sscanf(buffer, "%d", &code);
	switch(code)
	{
		//successor query
		case 100:
			fmt = "%*d %*s %s %*s %s";
			break;
		case 200:
			fmt = "%*d %*s %s";
			break;
		case 210:
			fmt = "%*d %*s %*s %s %*s %s";
			break;
		case 120:
			fmt = "%*d %*s %*s %s";
			break;
		case 320:
			fmt = "%*d %*s %s %*s %s";
			break;
		case 110:
		case 220:
		case 130:
		case 230:
		case 331:
		case 332:
			return message_alloc(code, NULL, NULL);
	}
	return _parse_message(fmt);
};
