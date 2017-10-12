/*** main.c  * from Aho, Sethi, Ullman**/

#include "global.h"
#include <stdio.h> /* added JWJ */
#include <time.h> /* added JWJ for time */

int main()
{
    contentIndex = 0;
    lineno = 1; 
	init();
    printf("recursive descent for expressions: Katie Long from Aho & JWJ\n");
    time_t t;
    time(&t); printf("%s\n",ctime(&t));
	parse();
	exit(0);  /* successful termination */
}

/********************************************************************/
