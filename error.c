/***********  error.c **from Aho, Sethi, Ullman***********/

#include "global.h"

void error(m)    /*generate all error messagese */
	char *m;
{
	fprintf(stderr, "\nline %d; %s\n", lineno, m);
    printf("Parsing failed.\n");
	exit(1);  /* unsuccessful termination  */
}

