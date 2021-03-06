/*
 * main.c
 *
 *  Created on: Jan 3, 2013
 *      Author: root
 */

//**************************************
//INCLUDE files
//**************************************
#include <stdio.h>
#include "encryption.h"

#define cypherbits 256 /* encryption strength in bits */
#define cypher cypherbits/(sizeof(int)*8)
int seed[cypher];

//**************************************
// Description:Encrypts file and outputs it to a file
//
// Inputs:file_encryption <infile> <outfile> <key>
//
//**************************************


int main(int argc,char *argv[]) {
    char banner[]="\x50\x72\x6f\x6a\x65\x63\x74\x20\x62\x79"
    "\x20\x43\x68\x61\x6e\x64\x61\x6e\x20\x4b\x75\x6d\x61\x72";

    char buf[2048];
    int p,r,l=0,i,t,s,x;
    char b,c,pct,lpct;
    FILE *infile=NULL,*outfile=NULL;
    fprintf(stderr, "**** %s ****\n", banner);
    if(argc!=4){
        fprintf(stderr,"use: %s <infile> <outfile> <key>\n",argv[0]);
        return -1;
    }

    if((infile=fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"Failed to open %s\n",argv[1]);
        return -1;
    } else {
        fseek(infile,0,SEEK_END);
        l=ftell(infile);
        rewind(infile);
        }

    if((outfile=fopen(argv[2],"w"))==NULL){
        fprintf(stderr,"Failed to create %s\n",argv[2]);
        return -1;
    }

    s=l;
    t=0;
    pct=0;
    if(l<1)fprintf(stderr,"Encrypting data.. (%d bit cypher)\n",cypher*sizeof(int)*8);
    else fprintf(stderr,"Encrypting %d bytes.. (%d bit cypher)\n",l,cypher*sizeof(int)*8);

    modseed();
    p=0;
    while(argv[3][p]!=0){
        modseed();
        seed[0]=seed[0]+argv[3][p];
        modseed();
        p++;
    }
    i=0;
    if(l>0){
        fputc('[',stderr);
        x=(l/sizeof(buf));
        if(l-x*sizeof(buf)!=0)x+=1;
        if(x>38)x=38;
        for(p=0;p<x;p++) fputc(32,stderr);
        fputc(']',stderr);
        fputc(13,stderr);
        fputc('[',stderr);
        fflush(stderr);
    }
    c=1;
    while(c){
        r=fread(&buf,1,sizeof(buf),infile);
        if(r>0) {
        	t+=r;
        	if(l>0){
            	lpct=pct;
            	pct=t/(l/x);
            	if(pct>lpct) {
                	fputc(88+32*i,stderr);
                	fflush(stderr);
                	i=1-i;
            	}
    	   } else {
        	fputc(88+32*i,stderr);
        	fflush(stderr);
        	i=1-i;
        	}
        	p=0;
        	while(p<r) {
            	modseed();
            	buf[p]=buf[p]^seedsum();
            	p++;
        	}
        	if(fwrite(&buf,1,r,outfile)!=r) {
            	fprintf(stderr,"\nerror writing data\n");
            	return -1;
        	}
        } else c=0;
    }
    if(l>0)fputc(']',stderr);
    fprintf(stderr,"\nDone. Wrote %d bytes in file \"%s\".\n",t, argv[2]);
}
