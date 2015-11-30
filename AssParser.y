%header{
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "AssemblyInfo.h"
#include <cstring>
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
list<AssemblyLabel*>  *gl_labels = new list<AssemblyLabel*>();
list<AssemblyLine*> *gl_lines = new list<AssemblyLine*>();
AssemblyExpression* expr =  new AssemblyExpression();


void handle(); 
void yyerror(const char *s);
char* startLabel;

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
%token <ival> HECXA
%token <ival> OCTAL
%token <ival> BINARY
%token <sval> ID
%token COLON
%token COMMA
%token <sval> OPERATOR
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%type <ival> direct_value
//%type <line> line component instruction
//%type <exp> argument expressions
%type <arg> literal

%start program
%%

// 8051 Assembly Grammar 2015

program:
	PUBLIC ID labels { std::cout << "Start Label" << $2 << std::endl;
						startLabel = $2;
						ass_program->labelList = gl_labels;
					}
	;
labels:
	labels label
	|label
	;
label:
	END_LINE ID COLON END_LINE lines { std::cout << "Label " << $2 << std::endl;
										AssemblyLabel* label = new AssemblyLabel();
										label->name = $2;
										label->lineList = gl_lines;
										gl_labels->push_back(label);
										gl_lines = new list<AssemblyLine*>();}
	|END_LINE ID COLON lines  { std::cout << "Label " << $2 << std::endl;
										AssemblyLabel* label = new AssemblyLabel();
										label->name = $2;
										label->lineList = gl_lines;
										gl_labels->push_back(label);
										gl_lines = new list<AssemblyLine*>();}
	;	
lines:
	lines line 
	|line 
	;
line:
	component COMMENT END_LINE   
	| component  END_LINE
	;
component:
	instruction 
	;
instruction:
	ID 		{   AssemblyLine* line = new AssemblyLine();
				line->kind = INSTRUCTION;
				line->name = $1;
				line->expList = gl_exps;
				gl_lines->push_back(line);
			    gl_exps = new list<AssemblyExpression*>();}
	|ID arguments  { AssemblyLine* line = new AssemblyLine();
				line->kind = INSTRUCTION;
				line->name = $1;
				line->expList = gl_exps;
				gl_lines->push_back(line);
			    gl_exps = new list<AssemblyExpression*>();
				}
	;
arguments:
	 argument 	
	 |arguments COMMA argument 
	 ;
argument:
	expressions	{gl_exps->push_back(expr);
				expr = new AssemblyExpression();}
	;
literal:
	| STRING {std::cout << "String " << $1 << std::endl;
				Arg a;
				a.c = $1;
				$$ = new AssemblyArgument(0 , a);
				}
	| FLOAT {std::cout << "FLOAT " << $1 << std::endl;
				Arg a;
				a.f = $1;
				$$ = new AssemblyArgument(2,a);}
	| '#' direct_value {std::cout << "Immediate Value " << $2 << std::endl;
						Arg a;
						a.i = $2;
						$$ = new AssemblyArgument(4,a);
						}
	| '#' ID   {std::cout << "Immediate Value " << $2 << std::endl;
				Arg a;
				a.c = $2;
				$$ = new AssemblyArgument(5,a);
			   }
	| direct_value {std::cout << "Direct Value " << $1 << std::endl;
					Arg a;
					a.i = $1;
					$$ = new AssemblyArgument(1,a);
					}
	| '@' ID {std::cout << "Indirect value " << $2 << std::endl;
					Arg a;
					a.c = $2;
					$$ = new AssemblyArgument(3,a);
					}
	| ID  {std::cout << "ID " << $1 << std::endl;
					Arg a;
					a.c = $1;
					$$ = new AssemblyArgument(6,a);}
	| ID '.' INT { std::cout << "BIT" << std::endl;
					std::stringstream ss;
  					ss << $1 << '.' << $3;
  					std::string tmp = ss.str();
  					char *cstr = new char[tmp.length() + 1];
					strcpy(cstr, tmp.c_str());

					Arg a;
					a.c = cstr;
					$$ = new AssemblyArgument(8,a);}
;
direct_value:
	 HECXA	{$$ = $1;}
	| OCTAL {$$ = $1;}
	| BINARY {$$ = $1;}
	| INT {$$ = $1;}
;
expressions:
	 expressions OPERATOR literal { 
	 								Arg a;
	 								a.c = $2;
	 								std::cout << "Operator " << a.c << std::endl;
	 								expr->kind = EXP_KIND(2); 								
	 								expr->argList.push_back(new AssemblyArgument(7,a));
	 								expr->argList.push_back($3);}
	| literal	{ expr->argList.push_back($1);}
	
;
%%


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

