#include <stdio.h>
#include <ctype.h>

/*Global Declarations ----- Variables*/

int charClass;

char lexme [100];

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

