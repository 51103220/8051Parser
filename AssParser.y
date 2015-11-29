%header{
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "AssemblyInfo.h"
%}

%{
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse(AssemblyProgram *ass_program);
extern "C" FILE *yyin;

// stuff to store information:
AssemblyProgram *ass_program = new AssemblyProgram();
list<AssemblyExpression*>  *gl_exps = new list<AssemblyExpression*>() ;
list<AssemblyArgument*>  *gl_args = new list<AssemblyArgument*>() ;

AssemblyLine* make_line(INST_KIND kind,char* name,list<AssemblyExpression*>  *exps);
AssemblyExpression* make_expr(EXP_KIND exp_kind, char* op, std::list<AssemblyArgument*> *argList);
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
	
	AssemblyLine* line;
	//list<AssemblyExpression*>* exps;
	AssemblyExpression* exp;
	//ArgumentList args;
	AssemblyArgument* arg;
}

%define PARSE_PARAM \
	AssemblyProgram *ass_program

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
%token <sval> OPERATOR
%token LB
%token RB
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%type <line> line component directive label instruction
%type <exp> argument unary_expression 
%type <arg> literal
%start program
%%

// Sparc Assembly Grammar 2015

program:
	lines 
	;
lines:
	line 	{	
					ass_program->lineList.push_back($1);
					
					gl_exps = new list<AssemblyExpression*>();
					}
	|lines line {	
					ass_program->lineList.push_back($2);
					
					gl_exps = new list<AssemblyExpression*>();}

	
	;
line:
	component COMMENT END_LINE {$$ = $1;}
	| component END_LINE {$$ = $1;}
	;
component:
	instruction {$$ = $1;}
	|directive 	{$$ = $1;}
	|label {$$ = $1;}
	;
directive:
	DOT ID arguments {	
						
						$$ = make_line(DIRECTIVE,$2,gl_exps);
					 }
	;
label:
	ID COLON     {	
						$$ = make_line(LABEL,$1,gl_exps);
					 }
	| DOT ID COLON  {	
						$$ = make_line(LABEL,$2,gl_exps);
					 }
	;
instruction:
	ID 	 	{ 
						$$ = make_line(INSTRUCTION,$1,gl_exps);
					 }
	|ID arguments { 
						$$ = make_line(INSTRUCTION,$1,gl_exps);
					 }
	;
arguments:
	 argument {	gl_exps->push_back($1);
	 			//gl_args = new list<AssemblyArgument*>();
	 			}
	 |arguments COMMA argument {gl_exps->push_back($3);
	 			//gl_args = new list<AssemblyArgument*>();
	 			}
	
	;
argument:
	 unary_expression	{$$ = $1;}
	| LEFT_SQ unary_expression RIGHT_SQ {$$ = $2;} 
	;
literal:
	INT 				{	stringstream ss;
							ss << $1;
							gl_args->push_back(new AssemblyArgument(DIRECT_VALUE,ss.str()));
						}
	| FLOAT
	| STRING 
	| REGISTER 
	| special_register
	| ID
	| DOT OPERATOR ID //Stupid DIRECTIVE ARGUMENT
;
special_register:
	REGISTER '(' DOT ID ')'
;
unary_expression:
	binary_expression 
	|OPERATOR INT {	
					std::cout << "OPEARTOR INT" << std::endl;
					$$ = make_expr(UNARY,$1,gl_args);
					}
;
binary_expression:
	 binary_expression OPERATOR literal 
	| literal
	
;
%%

AssemblyLine* make_line(INST_KIND kind,char* name,list<AssemblyExpression*> *exps){
	AssemblyLine* line = new AssemblyLine();
	line->kind = kind;
	line->name = name;
	line->expList = exps;
	return line; 
}
AssemblyExpression* make_expr(EXP_KIND exp_kind, char* op, std::list<AssemblyArgument*> *argList){
	AssemblyExpression* expr = new AssemblyExpression();
	expr->exp_kind = exp_kind;
	expr->op = op;
	expr->argList = argList;
	return expr;
}

void handle() {
	ass_program = new AssemblyProgram();
	ass_program->name = "Sparc";
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
		yyparse(ass_program);
	} while (!feof(yyin));
}
void yyerror(const char *s) {
	cout << "EEK, parse error! Dont Care Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}

