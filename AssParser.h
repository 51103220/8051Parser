#ifndef YY_AssParser_h_included
#define YY_AssParser_h_included
/*#define YY_USE_CLASS 
*/
#line 1 "/usr/share/bison++/bison.h"
/* before anything */
#ifdef c_plusplus
 #ifndef __cplusplus
  #define __cplusplus
 #endif
#endif


 #line 8 "/usr/share/bison++/bison.h"

#line 23 "AssParser.y"
typedef union {
	int ival;
	float fval;
	char *sval;
} yy_AssParser_stype;
#define YY_AssParser_STYPE yy_AssParser_stype
#ifndef YY_USE_CLASS
#define YYSTYPE yy_AssParser_stype
#endif

#line 21 "/usr/share/bison++/bison.h"
 /* %{ and %header{ and %union, during decl */
#ifndef YY_AssParser_COMPATIBILITY
 #ifndef YY_USE_CLASS
  #define  YY_AssParser_COMPATIBILITY 1
 #else
  #define  YY_AssParser_COMPATIBILITY 0
 #endif
#endif

#if YY_AssParser_COMPATIBILITY != 0
/* backward compatibility */
 #ifdef YYLTYPE
  #ifndef YY_AssParser_LTYPE
   #define YY_AssParser_LTYPE YYLTYPE
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
  #endif
 #endif
/*#ifdef YYSTYPE*/
  #ifndef YY_AssParser_STYPE
   #define YY_AssParser_STYPE YYSTYPE
  /* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
   /* use %define STYPE */
  #endif
/*#endif*/
 #ifdef YYDEBUG
  #ifndef YY_AssParser_DEBUG
   #define  YY_AssParser_DEBUG YYDEBUG
   /* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
   /* use %define DEBUG */
  #endif
 #endif 
 /* use goto to be compatible */
 #ifndef YY_AssParser_USE_GOTO
  #define YY_AssParser_USE_GOTO 1
 #endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_AssParser_USE_GOTO
 #define YY_AssParser_USE_GOTO 0
#endif

#ifndef YY_AssParser_PURE

 #line 65 "/usr/share/bison++/bison.h"

#line 65 "/usr/share/bison++/bison.h"
/* YY_AssParser_PURE */
#endif


 #line 68 "/usr/share/bison++/bison.h"

#line 68 "/usr/share/bison++/bison.h"
/* prefix */

#ifndef YY_AssParser_DEBUG

 #line 71 "/usr/share/bison++/bison.h"

#line 71 "/usr/share/bison++/bison.h"
/* YY_AssParser_DEBUG */
#endif

#ifndef YY_AssParser_LSP_NEEDED

 #line 75 "/usr/share/bison++/bison.h"

#line 75 "/usr/share/bison++/bison.h"
 /* YY_AssParser_LSP_NEEDED*/
#endif

/* DEFAULT LTYPE*/
#ifdef YY_AssParser_LSP_NEEDED
 #ifndef YY_AssParser_LTYPE
  #ifndef BISON_YYLTYPE_ISDECLARED
   #define BISON_YYLTYPE_ISDECLARED
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;
  #endif

  #define YY_AssParser_LTYPE yyltype
 #endif
#endif

/* DEFAULT STYPE*/
#ifndef YY_AssParser_STYPE
 #define YY_AssParser_STYPE int
#endif

/* DEFAULT MISCELANEOUS */
#ifndef YY_AssParser_PARSE
 #define YY_AssParser_PARSE yyparse
#endif

#ifndef YY_AssParser_LEX
 #define YY_AssParser_LEX yylex
#endif

#ifndef YY_AssParser_LVAL
 #define YY_AssParser_LVAL yylval
#endif

#ifndef YY_AssParser_LLOC
 #define YY_AssParser_LLOC yylloc
#endif

#ifndef YY_AssParser_CHAR
 #define YY_AssParser_CHAR yychar
#endif

#ifndef YY_AssParser_NERRS
 #define YY_AssParser_NERRS yynerrs
#endif

#ifndef YY_AssParser_DEBUG_FLAG
 #define YY_AssParser_DEBUG_FLAG yydebug
#endif

#ifndef YY_AssParser_ERROR
 #define YY_AssParser_ERROR yyerror
#endif

#ifndef YY_AssParser_PARSE_PARAM
 #ifndef __STDC__
  #ifndef __cplusplus
   #ifndef YY_USE_CLASS
    #define YY_AssParser_PARSE_PARAM
    #ifndef YY_AssParser_PARSE_PARAM_DEF
     #define YY_AssParser_PARSE_PARAM_DEF
    #endif
   #endif
  #endif
 #endif
 #ifndef YY_AssParser_PARSE_PARAM
  #define YY_AssParser_PARSE_PARAM void
 #endif
#endif

/* TOKEN C */
#ifndef YY_USE_CLASS

 #ifndef YY_AssParser_PURE
  #ifndef yylval
   extern YY_AssParser_STYPE YY_AssParser_LVAL;
  #else
   #if yylval != YY_AssParser_LVAL
    extern YY_AssParser_STYPE YY_AssParser_LVAL;
   #else
    #warning "Namespace conflict, disabling some functionality (bison++ only)"
   #endif
  #endif
 #endif


 #line 169 "/usr/share/bison++/bison.h"
#define	SNAZZLE	258
#define	TYPE	259
#define	END	260
#define	INT	261
#define	FLOAT	262
#define	STRING	263


#line 169 "/usr/share/bison++/bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
 #ifndef YY_AssParser_CLASS
  #define YY_AssParser_CLASS AssParser
 #endif

 #ifndef YY_AssParser_INHERIT
  #define YY_AssParser_INHERIT
 #endif

 #ifndef YY_AssParser_MEMBERS
  #define YY_AssParser_MEMBERS 
 #endif

 #ifndef YY_AssParser_LEX_BODY
  #define YY_AssParser_LEX_BODY  
 #endif

 #ifndef YY_AssParser_ERROR_BODY
  #define YY_AssParser_ERROR_BODY  
 #endif

 #ifndef YY_AssParser_CONSTRUCTOR_PARAM
  #define YY_AssParser_CONSTRUCTOR_PARAM
 #endif
 /* choose between enum and const */
 #ifndef YY_AssParser_USE_CONST_TOKEN
  #define YY_AssParser_USE_CONST_TOKEN 0
  /* yes enum is more compatible with flex,  */
  /* so by default we use it */ 
 #endif
 #if YY_AssParser_USE_CONST_TOKEN != 0
  #ifndef YY_AssParser_ENUM_TOKEN
   #define YY_AssParser_ENUM_TOKEN yy_AssParser_enum_token
  #endif
 #endif

class YY_AssParser_CLASS YY_AssParser_INHERIT
{
public: 
 #if YY_AssParser_USE_CONST_TOKEN != 0
  /* static const int token ... */
  
 #line 212 "/usr/share/bison++/bison.h"
static const int SNAZZLE;
static const int TYPE;
static const int END;
static const int INT;
static const int FLOAT;
static const int STRING;


#line 212 "/usr/share/bison++/bison.h"
 /* decl const */
 #else
  enum YY_AssParser_ENUM_TOKEN { YY_AssParser_NULL_TOKEN=0
  
 #line 215 "/usr/share/bison++/bison.h"
	,SNAZZLE=258
	,TYPE=259
	,END=260
	,INT=261
	,FLOAT=262
	,STRING=263


#line 215 "/usr/share/bison++/bison.h"
 /* enum token */
     }; /* end of enum declaration */
 #endif
public:
 int YY_AssParser_PARSE(YY_AssParser_PARSE_PARAM);
 virtual void YY_AssParser_ERROR(char *msg) YY_AssParser_ERROR_BODY;
 #ifdef YY_AssParser_PURE
  #ifdef YY_AssParser_LSP_NEEDED
   virtual int  YY_AssParser_LEX(YY_AssParser_STYPE *YY_AssParser_LVAL,YY_AssParser_LTYPE *YY_AssParser_LLOC) YY_AssParser_LEX_BODY;
  #else
   virtual int  YY_AssParser_LEX(YY_AssParser_STYPE *YY_AssParser_LVAL) YY_AssParser_LEX_BODY;
  #endif
 #else
  virtual int YY_AssParser_LEX() YY_AssParser_LEX_BODY;
  YY_AssParser_STYPE YY_AssParser_LVAL;
  #ifdef YY_AssParser_LSP_NEEDED
   YY_AssParser_LTYPE YY_AssParser_LLOC;
  #endif
  int YY_AssParser_NERRS;
  int YY_AssParser_CHAR;
 #endif
 #if YY_AssParser_DEBUG != 0
  public:
   int YY_AssParser_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
 #endif
public:
 YY_AssParser_CLASS(YY_AssParser_CONSTRUCTOR_PARAM);
public:
 YY_AssParser_MEMBERS 
};
/* other declare folow */
#endif


#if YY_AssParser_COMPATIBILITY != 0
 /* backward compatibility */
 /* Removed due to bison problems
 /#ifndef YYSTYPE
 / #define YYSTYPE YY_AssParser_STYPE
 /#endif*/

 #ifndef YYLTYPE
  #define YYLTYPE YY_AssParser_LTYPE
 #endif
 #ifndef YYDEBUG
  #ifdef YY_AssParser_DEBUG 
   #define YYDEBUG YY_AssParser_DEBUG
  #endif
 #endif

#endif
/* END */

 #line 267 "/usr/share/bison++/bison.h"
#endif
