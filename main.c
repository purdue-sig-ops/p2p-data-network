/*
 * File:   main.c
 * Author: caleb
 *
 * Created on September 22, 2012, 6:13 AM
 */

#include <stdio.h>
#include <stdlib.h>

#include "peer_recv.h"

/*
 *
 */
int main(int argc, char** argv) {

    init_listener(1597);
    return (EXIT_SUCCESS);
}

