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
struct temp_expr
{
	char* op;
	int LHS;
	int RHS;
	int value;   
}; 
struct bits{
	char* reg;
	unsigned pos;
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
   bits bit;
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
	void change(int i,Arg v){
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


class AssemblyLine{
public:
	char* name;
	INST_KIND kind;
	int offset;
	bool checked;
	std::list<AssemblyExpression*> *expList;
public:
	AssemblyLine(){
		checked = false;
		offset = 0;
	}
	~AssemblyLine(){}
};
class AssemblyLabel{
public:
	const char* name;
	unsigned int address;
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
	std::list<char*> bitReg;
public:
	AssemblyProgram(){
	}
	~AssemblyProgram(){}
};



