    /*** parser.c  **** *from Aho, Sethi, Ullman**************/

#include "global.h"

int lookahead;

void parse_conditional();
void parse_read();

// program -> LABEL lines
void parse()   /*parses and translates expression list  */
{
	lookahead = yylex(); /* was lookahead = laxan() */
    parse_lines();  //KL - starts the parsing process

    print_program(); //KL - prints the program if successful   

    // Sections added by KL ***********************
    // If we return from parse_lines, we made it through everything
    printf("\n\nParsing successful!\n");

    //Print all the symbols and the number of times they show up
    print_symbol_table();
}

// lines -> LABEL linesTail lines
void parse_lines()
{
    while( lookahead != DONE ){
        switch(lookahead){
            case NUMBER:
                match(lookahead);   //The first should be a label
                parse_linesTail();  //We should see a valid linesTail
                continue;           //Continue through while loop
            default:
                error("syntax error: lines must begin with a LABEL");
                printf("\n\nParsing Failed.\n"); 
                break;
        }
    }
}

// linesTail-> statement | BEGIN | END.
void parse_linesTail(){

    // We are either beginning or ending the program OR we have a statement
    // that we must parse more in depth.
    switch(lookahead){
        case START:     
            match(lookahead);
            break;
        case DONE:
            match(lookahead);
            break;
        default:
            parse_statement();
    }

}

// statement -> conditional gto | NULL';' gto | PRINT';' gto | assignment';' gto
void parse_statement(){
    
    switch(lookahead){
        case IF:
            parse_conditional(); 
            parse_goto();
            break;
        case NOTHING:
            match(lookahead);
            match(';');
            parse_goto();
            break;
        case PRNT:
            parse_print();
            match(';');
            parse_goto();
            break;
        case READIN:
            parse_read();
            match(';');
            parse_goto();
            break;
        case VARIABL:
            parse_assignment();
            match(';');
            parse_goto();
            break;
        default:
            error("syntax error- unrecognized statement\n");           
            printf("\r\rParsing failed!\r");
    }
}

// conditional -> IF expression GOTO NUMBER ELSE gto
void parse_conditional(){
    
    switch(lookahead){
        case IF:
            match(IF);
            expr();
            switch(lookahead){  //If the user decides to do IF ... THEN ... ELSE it will be accepted
            case THEN:
                match(lookahead);
                break;
            default:            //Also accepts just IF .. ELSE
                break;
            }
            match(GTO);
            match(NUMBER);
            match(ELSE);
            break;
        default:
            error("syntax error- malformed conditional\n");
            printf("\r\rParsing failed!\n");
    }
}

// prnt -> STRING | VARIABLE
void parse_print(){
    switch(lookahead){
        case PRNT:
            match(PRNT);
            switch(lookahead){
                case STRNG:
                    match(STRNG);                    
                    break;
                case VARIABL:
                    match(VARIABL);
                    break;
                case NUMBER:
                    match(NUMBER);
                    break;
                default:
                    error("syntax error- malformed print statment\n");
                    printf("\r\rParsing failed\n");
            }
            break;
        default:
            error("syntax error- malformed print statement\n");
            printf("\r\rParsing failed\n");
    }
}

// assignment -> variable '=' expression
void parse_assignment(){
    switch(lookahead){
        case VARIABL:
            match(VARIABL);
            match('=');
            expr();            
            break;
        default:
            error("syntax error- malformed assignment.\n");
            printf("\r\rParsing failed\n");

    }
}

// comparator -> var COMPARATOR (var|expr|num)
/*void parse_comparator(){
    switch(lookahead){
        case VARIABL:
            expr();
            match(CONDITION);
            expr();
            break;
        default:
            printf("Parsing failed\n");
            error("syntax error- malformed comparison statement\n");
    }
}*/

// gto -> GOTO number ';'
void parse_goto(){
    switch(lookahead){
        case GTO:
            match(lookahead);
            match(NUMBER);
            match(';');
            break;
        default:
            error("syntax error- malformed GOTO statement\n");
            printf("\r\rParsing failed\n");
    } 
}

// read -> READ variable ';'
void parse_read(){
    switch(lookahead){
        case READIN:
            match(lookahead);
            match(VARIABL);
            match(';');
            break;
        default:
            error("syntax error- malformed READ statement\n");
            printf("\r\rParsing failed\n");
    }
}

// End of large KL Section *********************

/*
E -> TE'
 parse_E(){
   parse_term();
   Parse_E'();
}


E'-> +TE' | epsilon
 parse_E'() {
   if (lookahead == '+') {
       match('+');
       parse_T();
       parse_E'();
      }
   else
    if (lookahead == '+') {
       match('+');
       parse_T();
       parse_E'();
     }
   else error("unexpected token");
 }

The resulting code is a result of:
  -  removing the tail recursion from parse_E'()
  -  inlining the modified parse_E'() in parse_E().

*/
void expr()
{
	int t;
	term();
	while(1)
		switch (lookahead) {
        // KL - Added conditions so that expressions now include conditional statements
        //      This helps in comparator cases x > y, x == y, etc
		case '+': case '-': case CONDITION:
			t=lookahead;
			match(lookahead); term(); emit(t, NONE);
			continue;
		default:
			return;
	}
}

/*
 T  -> FT'
 T' -> *FT' | epsilon 
 Similar steps: remove recursion, inline
*/
void term()
{
	int t;
	factor();
	while(1)
		switch(lookahead) {
        // KL - Added conditions so that expressions now include conditional statements
        //      This helps in comparator cases x > y, x == y, etc
		case '*': case '/' : case DIV: case CONDITION:
			t=lookahead;
			match(lookahead); factor(); emit (t, NONE);
			continue;
		default:
			return;
		}
}

/*
 F -> ( E ) | VARIABL | NUMBER
*/
void factor()
{
		switch(lookahead) {
			case '(':
				match('('); expr(); match(')'); break;
			case NUMBER:
				emit(NUMBER, tokenval); match(NUMBER); break;
			case VARIABL:
				emit(VARIABL, tokenval); match(VARIABL); break;
			default:
				error("syntax error");
                printf("\r\rParsing failed\n");
	}
}

void match(t)
	int t;
{
	if (lookahead == t){
    
    /* DEPRECATED: remains for reference so KL can learn from her mistakes!
    
     // Add the token to the program contents
        if (lookahead == NUMBER){
            // We want to convert this, otherwise if someone actually entered... say 43 as a number
            // Then 43 will be displayed instead of ASCII value 43, which is '+'
            char str[4096];
            sprintf(str, "%d", tokenval);
            nonIntegerContent[contentIndex] = str; 
            progContent[contentIndex] = 261;                
        }                     
        else if (lookahead == VARIABL || lookahead == STRNG || lookahead == CONDITION){
            //If it is a string or variable, store the string
            //or variable in the non integer content array
            progContent[contentIndex] = 261;                
            nonIntegerContent[contentIndex] = stringval;
        }
        else    
            progContent[contentIndex] = lookahead;
        contentIndex=contentIndex+1;*/
        
        // KL - without this check, will go ahead and grab NULL (0x0) for next value.
        //      Now it keeps the DONE value so it propogates up through the program.
		if (lookahead != DONE)
            lookahead = yylex();
    }
	else{
        error("syntax error - unexpected token");
        printf("\r\rParsing Failed\n");
    }
}

