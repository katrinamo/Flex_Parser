/***global.h******from Aho, Sethi, Ullman*************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'

#define START       256     // BEGIN
#define GTO         257     // GOTO
#define READIN      258     // READ
#define NOTHING     259     // NULL
#define PRNT        260     // PRINT
#define VARIABL     261     
#define OPERATOR    262     
#define CONDITION   263     
#define NUMBER      264     
#define EQUAL       265     
#define THEN        266     
#define CLOSEPAR    267        
#define STRNG       268     
#define DONE        269     

//Further Elaboration of some abstracted tokens
#define IF          270
#define ELSE        271

#define PLUS        272
#define MINUS       273  
#define DIV         274
#define MULT        275
                    
#define GREATER     276
#define LESS        277
#define NOTEQ       278
#define GREATEQ     279
#define LESSEQ      280
#define EXACT       281

#define  SYMMAX 100   /* size of symtable */
#define  PROGMAXSIZE 2000   // max lines is 2000

int progContent[PROGMAXSIZE];   //tokens are, IN GENERAL, stored as ints

char nonIntegerContent[PROGMAXSIZE][PROGMAXSIZE]; //tokens that we KNOW will be strings are 
                                       //stored as such
char * stringval;

int contentIndex;       //where in the input program we are
void print_program();   //prints the entirety of the program
void translate_value(); //translates the stored token value to the string
void clear_contents();  //clears any previously held programs

char yystring[1000];
int yylex();

int tokenval;    /* value of token atribute  */
int lineno;

typedef struct entry entry;
struct entry { /* form of symbol table entry */
  char *lexptr;
  int token;
  int count;
  entry *next;
  char str[];
};
entry *symtable[SYMMAX]; /* symbol table */
entry *tokensym; /* use in place of tokenval for identifiers */

void error(char *m);
entry* lookup(char s[], int current_token);
void parse();
void expre();
void match(int t);

void parse();
void expr();
void term();
void factor();
void match(int t);

int lexan();
void emit(int t, int tval);
void init();
void exit(int n);
int main();

void parse_lines();
void parse_linesTail();
void parse_statement();
void parse_conditonal();
void parse_print();
void parse_assignment();
void parse_comparator(); 
void parse_goto();
