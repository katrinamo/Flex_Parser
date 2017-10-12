// AUTHOR: Katie Long
// Loops through the array containing the program's content, printing the
// input content.

#include "global.h"
#include <string.h>
#include <stdlib.h>

//This is a simple mapping of token values to the strings they actually represent
const char * mappedContents [16] = {"BEGIN", "GOTO", "READ", "NULL", "PRINT", "VARIABLE", "OPERATOR", "CONDITION", "NUM    BER", "EQUAL", "THEN", ")", "STRING", "END.", "IF", "ELSE"};

// NAME: print_program
// DESCRIPTION: This program prints the contents of the input branch 441 program 
//              which has been split into two parts: integer content and non
//              integer content (AKA Strings and variables).
void print_program(){
    for(int i = 0; i < contentIndex; i++){
 /* DEPRECATED: here for KL's reference       
        //If it is an added token value, find the mapping
        if(progContent[i] > 255){
            
            //If it has been set to a variable, look for a non integer value
            if(progContent[i] == 261)
                printf("%s ", nonIntegerContent[i]);
            else{
                //Prints the value of the mapped content, offsetting for the length
                //of the mappedContents array.
                printf("%s ", mappedContents[progContent[i]-256]);
            }  
        }
        
        //Otherwise it's a normal token/not a keyword
        else{
            printf("%c ", progContent[i]);
        }
    }
*/
        printf("%s", nonIntegerContent[i]);
    }
    printf("\n");
}

// NAME: clear_contents
// DESCRIPTION: This program clears the contents of the arrays that recorded what
//              the input program looked like.
void clear_contents(){
  
    // sets all of the contents to 0
    memset(&progContent[0], 0, sizeof(progContent));
    memset(&nonIntegerContent[0], 0, sizeof(nonIntegerContent));
}
