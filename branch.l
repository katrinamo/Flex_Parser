%{
#include "global.h"
char buffer[PROGMAXSIZE];
%}

%option noyywrap

delim           [\t ]
ws              {delim}+
num         {digit}+
digit       [0-9]
letter      [a-zA-Z]
variable    {letter}({letter}|{digit})*
newline     [\n]
string      ["]


%%
"BEGIN"     {sprintf(buffer, "%s ", yytext);
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                return START;}
"GOTO"      {sprintf(buffer, "%s ", yytext);    
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                return GTO;}
"READ"      {sprintf(buffer, "%s ", yytext); 
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                return READIN;}
"NULL"      {sprintf(buffer, "%s ", yytext); 
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                return NOTHING;}
"PRINT"     {sprintf(buffer, "%s ", yytext); 
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                return PRNT;}
"IF"        {sprintf(buffer, "%s ", yytext); 
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                return IF;}
"ELSE"      {sprintf(buffer, "%s ", yytext); 
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                return ELSE;}
"THEN"      {sprintf(buffer, "%s ", yytext); 
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                return THEN;}
"END."      {sprintf(buffer, "%s ", yytext); 
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                return DONE;}

"+"             {sprintf(buffer, "%s ", yytext);    
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                    return '+';}
"-"             {sprintf(buffer, "%s ", yytext); 
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                    return '-';}
"/"             {sprintf(buffer, "%s ", yytext); 
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                    return '/';}
"*"             {sprintf(buffer, "%s ", yytext); 
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                    return '*';}

">"|"<"|"!="|"=="|">="|"<=" {sprintf(buffer, "%s ", yytext);
                            strcpy(nonIntegerContent[contentIndex], buffer);
                            contentIndex = contentIndex + 1;
                                return CONDITION;}           

";"             {sprintf(buffer, "%s ", yytext);    
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                    return ';';}
"="             {sprintf(buffer, "%s ", yytext);    
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                    return '=';}
"("             {sprintf(buffer, "%s ", yytext);    
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                    return '(';}
")"             {sprintf(buffer, "%s ", yytext);    
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                    return ')';}

\"(\\.|[^"\\])*\"            { /*taken from https://stackoverflow.com/questions/2039795/regular-expression-for-a-string-literal-in-flex-lex */  
                               sprintf(buffer, "%s ", yytext);    
                               strcpy(nonIntegerContent[contentIndex], buffer);
                               contentIndex = contentIndex + 1;
                               return STRNG;}

{variable}  {   sprintf(buffer, "%s ", yytext);   
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                if (strlen(yytext) >= BSIZE){
                    error("Variable name too long\n");
                }
                tokensym = lookup(yytext, VARIABL);
                return (int) tokensym->token;}

{num}       {   sprintf(buffer, "%s ", yytext);    
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                return NUMBER;}

{ws}        { /*nothing to do*/  }

"\n"        {   sprintf(buffer, "%s", yytext);      
                strcpy(nonIntegerContent[contentIndex], buffer);
                contentIndex = contentIndex + 1;
                lineno++;}

.           {   printf("COMPILER ERROR AT %s\n", yytext);
                error("UNKNWON SYMBOL\n");}
%%

