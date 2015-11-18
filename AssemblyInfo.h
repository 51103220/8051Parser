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
	DIRECTIVE
};

class AssemblyArgument(){
public:
	ARGS_KIND arg_kind;
	std::string value;	
public:
	AssemblyArgument(){}
	~AssemblyArgument(){}

}
class AssemblyExpression(){
public:
	EXP_KIND exp_kind;
	std::list<AssemblyArgument*> ArgList;
public:
	AssemblyExpression(){}
	~AssemblyExpression(){}
}

class AssemblyInstruction(){
public:
	INST_KIND inst_kind;
	std::string name;
	std::list<AssemblyExpression*> ExpList;
public:
	AssemblyInstruction(){}
	~AssemblyInstruction(){}
}

class AssemblyProc(){
public:
	std::string name;
	unsigned address;
	std::list<AssemblyInstruction*> InstList;
public:
	AssemblyProc(){}
	~AssemblyProc(){}
}

class AssemblySection(){
public:
	std::string name;
	std::list<AssemblyProc*> ProcList;
public:
	AssemblySection(){}
	~AssemblySection(){}
}

class AssemblyProgram(){
public:
	char* name;
	std::list<AssemblySection*> SectionList;
public:
	AssemblyProgram(){}
	~AssemblyProgram(){}
}