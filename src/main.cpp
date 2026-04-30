#include "process.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

int main()
{

	Process proc;
	std::cout << proc.getId("Gameteste");
	
	proc.attatch();
	proc.parceMaps();

	for (int i = 0; i < proc.regions.size(); i++) {
		std::vector<uint8_t> memoryPart = proc.readMemory(proc.regions[i].start, proc.regions[i].end - proc.regions[i].start);
		int value;
		for (int j = 0; proc.regions[i].end - proc.regions[i].start > j; j++) {
		
			std::memcpy(&value, memoryPart.data() + j, 4);
			uintptr_t memoryAddr = proc.regions[i].start + j;
			std::cout <<  "\n Memory Readed: " << value << "at Addr = " << memoryAddr;
			if (value == 10) {
				int newIntValue = 5;
				std::vector<uint8_t> newValue(sizeof(newIntValue));
				std::memcpy(newValue.data(),&newIntValue, sizeof(newIntValue));
				proc.writeMemory(memoryAddr, newValue);
			}
		}
	}
	proc.detatch();
}
