#include "Scanner.h"
#include <cstdint>
#include <cstring>



Scanner::Scanner()
{
}


bool Scanner::newScan()
{
	Scanner::memorySnapshot.clear();
	proc.attatch();
	proc.parceMaps();
	for (int i = 0; i < proc.regions.size(); i++)
	{
		MemorySnapshot snapshot;
		snapshot.bytes = proc.readMemory(proc.regions[i].start, proc.regions[i].end - proc.regions[i].start);
		snapshot.start = proc.regions[i].start;
		Scanner::memorySnapshot.push_back(snapshot);
	}
	proc.detatch();
	return true;
}

std::vector<uintptr_t> Scanner::getMemoryAddrList()
{
	return Scanner::memoryAddrList;
}
