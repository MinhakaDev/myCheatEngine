#include "process.h"
#include <string>

int main()
{
	Process proc;
	int procId = proc.getId("Gameteste");
	std::cout << "procId = " + std::to_string(procId) + "\n";
	proc.parceMaps(procId);
	

}
