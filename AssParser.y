%{
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void handle(); 
void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	int ival;
	float fval;
	char *sval;
}

// define the constant-string tokens:
%token COMMENT
%token END_LINE
%token DOT
%token ID
%token COLON
%token COMMA
%token REGISTER
%token SPECIAL_REGISTER
%token OPERATOR
%token LEFT_SQ 
%token RIGHT_SQ 
%token DIR_
%token OPERATOR
// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%start program
%%

// Sparc Assembly Grammar 2015

program:
	lines
	;
lines:
	lines line
	|line
	
	;
line:
	component COMMENT END_LINE
	| component END_LINE
	;
component:
	directive 
	| label { std::cout << "Label"  << std::endl;}
	| instruction 
	;
directive:
	DOT ID { std::cout << "Directive: " << std::endl;} arguments
	|DOT ID
	
	;
label:
	ID COLON
	;
instruction:
	ID
	|ID arguments
	;
arguments:
	 arguments COMMA argument
	|argument 
	
	;
argument:
	| expression
	| LEFT_SQ expression RIGHT_SQ
	| DIR_
	;
literal:
	INT
	| FLOAT
	| STRING 
	| REGISTER 
	| SPECIAL_REGISTER
	| ID
;
expression:
	 expression OPERATOR literal 
	| literal
	

%%

void handle() {
	// open a file handle to a particular file:
	FILE *myfile = fopen("assembly", "r");
	// make sure it's valid:
	if (!myfile) {
		cout << "I can't open a.snazzle.file!" << endl;
		return ;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));
	
}

void yyerror(const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}