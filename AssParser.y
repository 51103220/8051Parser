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
%token <sval> ID
%token COLON
%token COMMA
%token REGISTER
%token SPECIAL_REGISTER
%token OPERATOR
%token LEFT_SQ 
%token RIGHT_SQ
%token OPERATOR
%token LB
%token RB
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
	| label
	| instruction 
	;
directive:
	DOT ID arguments {std::cout << "Directive :" << $2 << std::endl;}
	|DOT ID
	
	;
label:
	ID COLON {std::cout << "Label: " << $1 << std::endl;}
	;
instruction:
	ID 	{std::cout << "Opcode: " << $1 << std::endl;}
	|ID {std::cout << "Opcode: " << $1 << std::endl;} arguments 	
	;
arguments:
	 arguments COMMA argument
	|argument 
	
	;
argument:
	| expression
	| LEFT_SQ expression RIGHT_SQ
	;
literal:
	INT
	| FLOAT
	| STRING 
	| REGISTER 
	| special_register
	| ID
;
special_register:
	REGISTER '(' DOT ID ')' {std::cout << "Label:"<< $4 << std::endl;}
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