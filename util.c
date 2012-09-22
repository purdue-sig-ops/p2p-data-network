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