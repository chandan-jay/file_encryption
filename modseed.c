/*
 * modseed.c
 *
 *  Created on: Jan 3, 2013
 *      Author: root
 */
#include <stdio.h>
#include "encryption.h"
#define cypherbits 256 /* encryption strength in bits */
#define cypher cypherbits/(sizeof(int)*8)
int seed[cypher];

void modseed() {
    int x;
    for(x=1;x<cypher;x++)seed[x]=seed[x]*0x81772012+seed[x]+0x49122035+seed[x+1];
    for(x=1;x<cypher;x++)seed[0]=seed[0]^seed[x];
}
