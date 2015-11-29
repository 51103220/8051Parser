#include <vector>
#include <set>
#include <list>
#include <map>
#include <iostream>	
using namespace std;


enum ARGS_KIND{
	STRING = 0,
	REGISTER,
	SPECIAL_REGISTER,
	DIRECT_VALUE
};

enum EXP_KIND{
	LITERAL = 0,
	UNARY,
	BINARY
};

enum INST_KIND{
	INSTRUCTION = 0,
	DIRECTIVE,
	LABEL
};

class AssemblyArgument{
public:
	ARGS_KIND arg_kind;
	std::string value;	
public:
	AssemblyArgument(ARGS_KIND kind,std::string v){
		arg_kind = kind;
		value = v;
	}
	~AssemblyArgument(){}

};
class AssemblyExpression{
public:
	EXP_KIND exp_kind;
	char const* op;
	std::list<AssemblyArgument*> *argList;
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
	std::string name;
	INST_KIND kind;
	std::list<AssemblyExpression*> *expList;
public:
	AssemblyLine(){
	
	}
	~AssemblyLine(){}
};

class AssemblyProgram{
public:
	std::string name;
	std::list<AssemblyLine*> lineList;
public:
	AssemblyProgram(){
	}
	~AssemblyProgram(){}
};

class ExpressionList {
public:	
	list<AssemblyExpression*> expList;

	ExpressionList() {

	}
	~ExpressionList(){}
};
class ArgumentList{
public:
	std::list<AssemblyArgument*> argList;

	ArgumentList(){

	}
	~ArgumentList(){

	}
};


