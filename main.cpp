#include "AssParser.cpp"
using namespace std;

int main(int, char**) {
	handle();
	list<AssemblyArgument*>::iterator ii;
	for (ii = arg_list.begin();ii != arg_list.end(); ii++)
	{
		std::cout << "Value:" << (*ii)->value << std::endl;
	}
		
	return 0;
}