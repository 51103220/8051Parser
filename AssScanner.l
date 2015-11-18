%{
#include <iostream>
#include <string.h>
#include "AssParser.h"
using namespace std;
#define YY_DECL extern "C" int yylex()
%}
%%
[ \t] ;
\n        { return END_LINE; }
(\!.*)           { return COMMENT; }
\.            { return DOT; }
[A-Za-z_\$\@\#][A-Za-z_$0-9]*  {yylval.sval=strdup(yytext);return ID;}
\:			{return COLON;}
\,			{return COMMA;}
[0-9]+\.[0-9]+ { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+         { yylval.ival = atoi(yytext); return INT; }
\"(\\.|[^\\"])*\"  { yylval.sval = strdup(yytext); return STRING;}
\%[A-Za-z_$@0-9]+				{return REGISTER;}
\(				{return '(';}
\)				{return ')';}
[\+\-]			{return OPERATOR;}
\[				{return LEFT_SQ;}
\]				{return RIGHT_SQ;}
.              ;
%%
