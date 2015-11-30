#include <vector>
#include <set>
#include <list>
#include <map>
#include <iostream>	
using namespace std;


enum ARGS_KIND{
	STRING = 0,
	DIRECT_INT = 1,
	DIRECT_FLOAT = 2,
	INDIRECT = 3,
	IMMEDIATE_INT = 4,
	IMMEDIATE_ID = 5,
	ID = 6,
	OPERATOR = 7,
	BIT = 8
};

enum EXP_KIND{
	LITERAL = 0,
	UNARY = 1,
	BINARY = 2 
};

enum INST_KIND{
	INSTRUCTION = 0,
	DIRECTIVE = 1,
	LABEL =2
};
union Arg {
   int i;
   float f;
   char* c;
};
class AssemblyArgument{
public:
	ARGS_KIND kind;
	Arg value;	
public:
	AssemblyArgument(int i,Arg v){
		kind = ARGS_KIND(i);
		value = v;
	}
	~AssemblyArgument(){}

};
class AssemblyExpression{
public:
	EXP_KIND kind;
	list<AssemblyArgument*>argList;
public:
	AssemblyExpression(){}
	~AssemblyExpression(){}
};

class AssemblyInstruction{
public:
	INST_KIND inst_kind;
	std::string* name;
	std::list<AssemblyExpression*> *ExpList;
public:
	AssemblyInstruction(){
		inst_kind = INSTRUCTION;
		name = NULL;
		ExpList = NULL;
	}
	~AssemblyInstruction(){}
};

class AssemblyProc{
public:
	std::string* name;
	unsigned address;
	std::list<AssemblyInstruction*> *InstList;
public:
	AssemblyProc(){
		name = NULL;
		address = 0;
		InstList = NULL;
	}
	~AssemblyProc(){}
};

class AssemblySection{
public:
	std::string* name;
	std::list<AssemblyExpression*> *ExpList;
	std::list<AssemblyProc*> *ProcList;
public:
	AssemblySection(){
		name = NULL;
		ExpList = NULL;
		ProcList =NULL;
	}
	~AssemblySection(){}
};

class AssemblyLine{
public:
	char* name;
	INST_KIND kind;
	std::list<AssemblyExpression*> *expList;
public:
	AssemblyLine(){
	
	}
	~AssemblyLine(){}
};
class AssemblyLabel{
public:
	char* name;
	std::list<AssemblyLine*> *lineList;
public:
	AssemblyLabel(){
	
	}
	~AssemblyLabel(){}
};


class AssemblyProgram{
public:
	std::string name;
	std::list<AssemblyLabel*> *labelList;
public:
	AssemblyProgram(){
	}
	~AssemblyProgram(){}
};



