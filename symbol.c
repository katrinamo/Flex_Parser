/****    symbol.c   ****from Aho, Sethi, Ullman****/

#include "global.h" /*contains def of symboltable*/
#include "string.h"


/* Hashing comes from Algorithms and Data Structures handout */
enum { MULTIPLIER = 31 };
/* hash: compute hash value of string */
unsigned int hash(char *str)
{
  unsigned int h;
  unsigned char *p;

  h = 0;
  for (p = (unsigned char *) str; *p != 0; p++)
      h = MULTIPLIER * h + *p;
  return h % SYMMAX;
}

entry* lookup(char *s, int current_token)
{
        int h;
        entry *sym;

        h = hash(s);
        for (sym = symtable[h]; sym != NULL; sym = sym->next)
            if (strcmp(s, sym->lexptr) == 0){
               sym->count = sym->count + 1; 
               return sym;
            }
                

        /* Create if not found */
        sym = (entry *) malloc(sizeof(entry));
        sym->count = 1;

        //KL *********************
        //we need to malloc the space for the string to free it later
        //have to add 1 for the null terminator because it is a string
        char* strAlloc = malloc(strlen(s)+1); 
        sym->lexptr = strAlloc; //Now we have the appropriate space and we need to fill it
        strcpy(sym->lexptr, s); //We fill it with the string we are adding into the sym table!
        // KL *********************

        sym->token = current_token;
        sym->next = symtable[h];
        symtable[h] = sym;
        return sym;
}

// Provided by Dr. Jaromczyk
// Goes through the symbol table and prints out all of the symbols in the map
void print_symbol_table() 
{       
    printf("\nSYMBOL TABLE:\n");    
    for (int i = 0; i < SYMMAX; i++) {
        entry *sym = symtable[i];
        // Symbol is NULL if the entry in the table is empty
        if (sym != NULL){
            printf("    %s: %i\n", sym->lexptr, sym->count);
            free(sym->lexptr);
            free(sym);
        }
    }
}
