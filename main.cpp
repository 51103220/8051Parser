#include "AssParser.cpp"
using namespace std;
void print_arg(AssemblyExpression *expr){
	list<AssemblyArgument*>::iterator ai;
	std::cout << "\t\t\t\t\t "; 
	for(ai = expr->argList.begin(); ai != expr->argList.end(); ai++ ){
			switch ((*ai)->kind){
				case 0:
				case 7:
				case IMMEDIATE_ID:
				case 6:
				case INDIRECT:
					std::cout << (*ai)->value.c << " ";
					break;
				case DIRECT_FLOAT:
					std::cout << (*ai)->value.f << " ";
					break;
				case IMMEDIATE_INT:
				case DIRECT_INT:
					std::cout << (*ai)->value.i << " ";
					break;
				case 8:
					std::cout << (*ai)->value.c  << " "; 
					break;
				default:
					break;
			}
		}
}
void print_ass(AssemblyProgram* ass_program){
	list<AssemblyArgument*>::iterator ai;
	list<AssemblyLine*>::iterator li;
	list<AssemblyExpression*>::iterator ei;
	list<AssemblyLabel*>::iterator lbi;
	if (ass_program){
		std::cout << "***Assembly Name " << ass_program->name << std::endl; 
		std::cout << "***Number of labels " << ass_program->labelList->size() << std::endl;
		for(lbi = ass_program->labelList->begin();lbi != ass_program->labelList->end(); lbi++){
			std::cout << "\t Label name: " << (*lbi)->name << std::endl;
			std::cout << "\t Number of lines: " << (*lbi)->lineList->size() << std::endl;
			for(li = (*lbi)->lineList->begin(); li != (*lbi)->lineList->end(); li++ ){
				std::cout << "\t\t Opcode " << (*li)->name << std::endl;
				std::cout << "\t\t\t Number of Expression: " << (*li)->expList->size() << std::endl;
				bool first = false;
				for(ei = (*li)->expList->begin(); ei != (*li)->expList->end(); ei++ ){
					std::cout << "\t\t\t\t Number of Arguments:" << (*ei)->argList.size() << std::endl;
					print_arg((*ei));
					std::cout << std::endl; 
				}
			}
		}

	}
}
int main(int, char**) {
	std::cout << "------START PARSING------\n";
	handle();
	std::cout << "-----PARSING RESULT------\n";
	print_ass(ass_program);
		
	return 0;
}