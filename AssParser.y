%{
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "AssemblyInfo.h"
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse(std::list<AssemblyArgument*> *arg_list);
extern "C" FILE *yyin;

// stuff to store information:
AssemblyProgram *program = new AssemblyProgram();

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
%define PARSE_PARAM \
	std::list<AssemblyArgument*> *arg_list

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
	instruction 
	|directive 
	|label 
	;
directive:
	DOT ID arguments {std::cout << "Directive :" << $2 << std::endl;}
	;
label:
	ID COLON {std::cout << "Label: " << $1 << std::endl;}
	| DOT ID COLON {std::cout << "Label: " << $2 << std::endl;}
	;
instruction:
	ID 	{std::cout << "Opcode: " << $1 << std::endl;}
	|ID {std::cout << "Opcode: " << $1 << std::endl;} arguments 	
	;
arguments:
	 argument
	 |arguments COMMA argument 
	
	;
argument:
	 unary_expression
	| LEFT_SQ unary_expression RIGHT_SQ
	;
literal:
	INT 				{std::cout << "INTEGER " << $1 << std::endl;
							std::ostringstream ss;
							ss << $1;
							arg_list->push_back(new AssemblyArgument(DIRECT_VALUE,ss.str()));
						}
	| FLOAT
	| STRING 
	| REGISTER 
	| special_register
	| ID
	| DOT OPERATOR ID //Stupid DIRECTIVE ARGUMENT
;
special_register:
	REGISTER '(' DOT ID ')' {std::cout << "Label:"<< $4 << std::endl;}
;
unary_expression:
	binary_expression
	|OPERATOR INT
;
binary_expression:
	 binary_expression OPERATOR literal 
	| literal
	
;
%%

void handle() {
	program->name = "FUCK";
	// open a file handle to a particular file:
	FILE *myfile = fopen("assembly", "r");
	// make sure it's valid:
	if (!myfile) {
		cout << "I can't open a assembly file!" << endl;
		return ;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	do {
		yyparse(&arg_list);
	} while (!feof(yyin));
	
}

void yyerror(const char *s) {
	cout << "EEK, parse error! Dont Care Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}