#include <stdlib.h>
#include "util.h"

void error (char * message)
{
    perror(message);
    exit(ERR);
}

void error_t (int type, char * message)
{
    perror(message);
    exit(type);
}

int logb2 (int num)
{
	int log = 0;
	while ((num >> log) != 0) log++;

	return log;
}
