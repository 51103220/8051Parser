#include "AssParser.cpp"
using namespace std;

void print_line(AssemblyLine * line){
	switch (line->kind){
		case DIRECTIVE:
				std::cout << "DIRECTIVE:\n";
				std::cout << "\t" << line->name << " ";
				break;
		case INSTRUCTION: 
				std::cout << "INSTRUCTION:\n";
				std::cout << "\t" << line->name << " ";
				break;
		case LABEL: 
				std::cout << "LABEL:\n";
				std::cout << "\t" << line->name << " ";
				break;
		default: break;
	}	
}

void print_expression(AssemblyExpression* expr){
	switch (expr->exp_kind){
		case UNARY:
				std::cout << expr->op << expr->argList->size();
				break;
		default: break;
	}
}

int main(int, char**) {
	handle();
	/*list<AssemblyArgument*>::iterator ai;
	list<AssemblyLine*>::iterator li;
	list<AssemblyExpression*>::iterator ei;
	if (ass_program){
		for (li = ass_program->lineList.begin();li != ass_program->lineList.end(); li++)
		{	
			print_line(*li);
			list<AssemblyExpression*> *tempExpList = (*li)->expList;
			for(ei = tempExpList->begin(); ei != tempExpList->end(); ei++){
					//print_expression(*ei);
					if (*ei == tempExpList->front() && *ei == tempExpList->back())
						print_expression(*ei);
					else
					{
						if (*ei != tempExpList->back()){
							print_expression(*ei);
							std::cout << ",";
						}
						else
							print_expression(*ei);
					}

			}
			std::cout << "\n";
		}	
	}*/
		
	return 0;
}