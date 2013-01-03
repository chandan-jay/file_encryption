/*
 * seedsum.c
 *
 *  Created on: Jan 3, 2013
 *      Author: root
 */
#include <stdio.h>
#include "encryption.h"

#define cypherbits 256 /* encryption strength in bits */
#define cypher cypherbits/(sizeof(int)*8)
int seed[cypher];

int seedsum() {
    int n,x;
    n=0x80379251;
    for(x=0;x<cypher;x++)n=n^seed[x];
    return((n>>24)^((n>>16)&255)^((n>>8)&255)^(n&255));
}
