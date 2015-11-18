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
	std::list<AssemblyArgument*> *ArgList;
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

class AssemblyProgram{
public:
	std::string name;
	std::list<AssemblySection*> *SectionList;
public:
	AssemblyProgram(){
		name = "NULL";
		SectionList = NULL;
	}
	~AssemblyProgram(){}
};

// Global Variables help storing datas
AssemblySection* ass_section;
std::list<AssemblySection*> section_list;

AssemblyProc* ass_proc;
std::list<AssemblyProc*> proc_list;

AssemblyInstruction* ass_inst;
std::list<AssemblyInstruction*> inst_list;

AssemblyExpression* ass_exp;
std::list<AssemblyExpression*> exp_list;

std::list<AssemblyArgument*> arg_list;