#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Global Declarations ----- Variables

char nextChar;

int nextToken;

FILE *in_fp, *fopen();

int charClass;

char lexeme [100];

char * expression = NULL;

int temp;

int lexLen;

size_t len = 0;

ssize_t read;

int current;

int token;


//Function Declarations
void addChar();
void getChar();
void getNonBlank();
int lex();
void expr();
void factor();
void term();
void error();
//Character classes
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

int main(int argc, char *argv[]) {
  if (argc == 2){
    if ((in_fp = fopen(argv[1], "r")) == NULL)
      printf("ERROR - cannot open front.in \n");
    else {
      while ((read = getline(&expression, &len, in_fp)) != -1) {
        printf("\nRetrieved line of length %zu :\n", read-1);
        if(read-1 != 0){
          printf("Analysis for the expression: %s", expression);
          memset(errorstring,0,sizeof(errorstring));
          current = 0;
          getChar();
          if (expression != NULL){
            do {
              lex();
              expr();
            } while (nextToken != EOF);
          }
        }else{
          printf("This was a blank line\n");
        }
      }
    }
  }
  else{
    printf("error in reading filename\n");
  }
}
  
/*--------------------------------------------------*/
  
  
// lookup - a function to lookup operators and parentheses and return the token 
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
}//end of switch
  
/*--------------------------------------------------*/ 

  
void factor(){
  printf("Enter <factor>\n");
  if (nextToken == IDENT || nextToken == INT_LIT)
  // Get the next token 
  lex();
  else{
    if (nextToken == LEFT_PAREN){
      lex();
      expr();
      if (nextToken == RIGHT_PAREN)
      lex();
      else
      error();
    } 
      else
      error();
    } /* End of else */
    printf("Exit <factor>\n");;
} //end of function

/*--------------------------------------------------*/

  //this function gets the next character of input and determines a class
void getCharOld() {
  if ((nextChar = getc(in_fp)) != EOF) {
    if (isalpha(nextChar))
    charClass = LETTER;
    else if (isdigit(
      nextChar))
      charClass = DIGIT;
      else charClass = UNKNOWN;
    }
    else
    charClass = EOF;
}

/*--------------------------------------------------*/  


     // this function is used to get the next character of input 
  void getChar() {
  if (expression[current] != '\n' && expression[current] != EOF) {
    nextChar = expression[current];
    errorstring[current] = nextChar;
    temp = current;
    current++;

    if (isalpha(nextChar))
    charClass = LETTER;
    else if (isdigit(
      nextChar))
      charClass = DIGIT;
      else charClass = UNKNOWN;
    }
    else
    charClass = EOF;
}//end of function
  

/*--------------------------------------------------*/
  
  
   // this function adds nextChar to lexeme
 void addChar(){
   if (lexLen <= 98){
    lexeme[lexLen++] =nextChar;
    lexeme[lexLen] =0;
  }
  else
  printf("Error: lexeme is too long \n");
}//end of function
   
/*--------------------------------------------------*/
  
  
  //function will return a non white space character
  
void getNonBlank(){  
  while (isspace(nextChar))
  getChar();
}//end of function
  
/*--------------------------------------------------*/
  
  
  //lexical analyzer for arithmetic expressions

int lex(){
  lexLen = 0;
  getNonBlank();
  switch (charClass){
    case LETTER:
    addChar();
    getChar();
    while (charClass == LETTER || charClass == DIGIT){
      addChar();
      getChar();
    }
    nextToken = IDENT;
    break;
    case DIGIT:
    addChar();
    getChar();
    while (charClass == DIGIT){
      addChar();
      getChar();
    }
    nextToken = INT_LIT;
    break;
    case UNKNOWN:
    lookup(nextChar);
    getChar();
    break;
    // EOF case
    case EOF:
    nextToken = EOF;
    lexeme[0] = 'E';
    lexeme[1] = 'O';
    lexeme[2] = 'F';
    lexeme[3] = 0;
    break;
  } //end of switch
  printf("Next token is: %d, Next lexeme is %s\n",
  nextToken, lexeme);
  return nextToken;
} //end of function
  
/*--------------------------------------------------*/
  
  /*parses strings in the necesary language...
  rule:
    <expr> -> <term> {(+ | -) <term>}*/
  
void expr(){
  printf("Enter <expr>\n");
  term();
  while (nextToken == ADD_OP || nextToken == SUB_OP){
    lex();
    term();
  }
  printf("Exit <expr>\n");
} //end of function

/*--------------------------------------------------*/
  
void term(){
  printf("Enter <term>\n");
  factor();
  while (nextToken == MULT_OP || nextToken == DIV_OP){
    lex();
    factor();
  }
  printf("Exit <term>\n");
} //end of function

/*--------------------------------------------------*/

//standard error function
void error(){
  if (strcmp(lexeme, "EOF") == 0){
    printf("    Error function called\n");
    printf("    Error expression %s\n", errorstring);
    printf("    Error in: %s\n", previouslexeme);
  }
  else{
    printf("    Error function called\n");
    printf("    Error expression %s\n", errorstring);
    printf("    Error in: %s\n", lexeme);
  }
}
