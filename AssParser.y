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


%union {
	int ival;
	float fval;
	char *sval;
	
	AssemblyLine* line;
	AssemblyExpression* exp;
	AssemblyArgument* arg;
}

%define PARSE_PARAM \
	AssemblyProgram *ass_program

// define the constant-string tokens:
%token PUBLIC
%token COMMENT
%token END_LINE
%token END_OF_LINE
%token HECXA
%token OCTAL
%token BINARY
%token <sval> ID
%token COLON
%token COMMA
%token <sval> OPERATOR
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%type <line> line component instruction
%type <exp> argument expressions
//%type <arg> literal

%start program
%%

// 8051 Assembly Grammar 2015

program:
	PUBLIC ID labels { std::cout << "Start Label" << $2 << std::endl;}
	;
labels:
	labels label
	|label
	;
label:
	END_LINE ID COLON END_LINE lines { std::cout << "Label " << $2 << std::endl;}
	|END_LINE ID COLON lines  { std::cout << "Label " << $2 << std::endl;}
	;	
lines:
	lines line { ass_program->lineList.push_back($2);
				  gl_exps = new list<AssemblyExpression*>();}
	|line 	  { ass_program->lineList.push_back($1);
				gl_exps = new list<AssemblyExpression*>();}
	;
line:
	component COMMENT END_LINE   {$$ = $1;}
	| component  END_LINE{$$ = $1;}
	;
component:
	instruction {$$ = $1;}
	;
instruction:
	ID 		{ $$ = make_line(INSTRUCTION,$1,gl_exps);}
	|ID arguments  { $$ = make_line(INSTRUCTION,$1,gl_exps);}
	;
arguments:
	 argument 	{	gl_exps->push_back($1);}
	 |arguments COMMA argument {gl_exps->push_back($3);}
	;
argument:
	expressions	{$$ = $1;} 
	;
literal:
	INT 				{	stringstream ss;
							ss << $1;
							gl_args->push_back(new AssemblyArgument(DIRECT_VALUE,ss.str()));
						}
	| STRING
	| FLOAT 
	| '#' direct_value
	| '#' ID
	| direct_value
	| '@' ID
	| ID
;
direct_value:
	 HECXA
	| OCTAL
	| BINARY
	| INT 
;
expressions:
	 expressions OPERATOR literal { std::cout << "Binary\n";}
	| literal	{ std::cout << "Literal\n";}
	
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
	ass_program->name = "8051";
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

