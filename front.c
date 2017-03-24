#include <stdio.h>
#include <ctype.h>

/*Global Declarations ----- Variables*/

int charClass;

char lexeme [100];

char nextChar;

int lexLen;

int token;

int nextToken;

FILE *in_fp, *fopen();

/*Function Declarations*/
void addChar();
void getChar();
void getNonBlank();
int lex();
void expr();
void factor();
void term();
void error();

/*Character classes*/
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/*main*/

int main(){
  int main(){
  if ((in_fp = fopen("front.in", "r")) == NULL)
f    printf("ERROR: failed to open input file \n");
  else{
    getChar();
    do{
      lex();
      expr();
    } while (nextToken != EOF);
  }
}
  
/* lookup - a function to lookup operators and parentheses
and return the token */
int lookup(char ch){
  switch (ch){
    case '(':
      addChar();
      nextToken = LEFT_PAREN;
      break;
    case ')':
      addChar();
      nextToken = RIGHT_PAREN;
      break;
    case '+':
      addChar();
      nextToken = ADD_OP;
      break;
    case '-':
      addChar();
      nextToken = SUB_OP;
      break;
    case '*':
      addChar();
      nextToken = MULT_OP;
      break;
    case '/':
      addChar();
      nextToken = DIV_OP;
      break;
    default:
      addChar();
      nextToken = EOF;
      break;
    }
    return nextToken;
}

