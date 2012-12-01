#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
//init a msg
static void msg_init(msg * dst, int code, char * hash_buf, char * addr)
{
	dst->code = code;
	if(hash_buf != NULL)
		id_init(&dst->ident, hash_buf);
	if(addr != NULL)
	{
		//TODO: Parse ip address
	}
}

//parse a message from the tcp buffer
void parse_message(msg * dst, const char * buffer)
{
	//message code
	int code = -1;
	//format string for extracting message details
	const char * fmt = NULL;
	char hash_buf[M/8 + 1];
	char addr[37 + 1];
	sscanf(buffer, "%d", &code);
	switch(code)
	{
		//successor query
		case 100:
			fmt = "%*d %*s %s %*s %s";
			break;
		//successor response
		case 200:
			fmt = "%*d %*s %s";
			break;

		//predecessor response
		case 210:
			fmt = "%*d %*s %*s %s %*s %s";
			break;
		//notify message
		case 120:
			fmt = "%*d %*s %*s %s";
			break;
		//status response
		case 320:
			fmt = "%*d %*s %s %*s %s";
			break;
		case 110:
		case 220:
		case 130:
		case 230:
		case 331:
		case 332:
			msg_init(dst, code, NULL, NULL);
			return;
	}
	sscanf(buffer, fmt, hash_buf, addr);
	msg_init(dst, code, hash_buf, addr);
}
