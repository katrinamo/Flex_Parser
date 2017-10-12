/****  init.c  ***from Aho, Sethi, Ullman*********/


#include "global.h"

struct entry keywords[] = {
  {0, 0}
};
void init()   /* loads keywords into symtable  */
{
	struct entry *p;
	for (p= keywords; p-> token; p++)
		lookup(p->lexptr, p->token); /* lookup now inserts if missing */
}


