#pragma once


#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <fcntl.h>

struct MemoryRegion
{
	uintptr_t start;
	uintptr_t end;
};

class Process
{
	private:
		int pid;
		std::vector<MemoryRegion> regions;
	public:

	int getId(std::string name);

	std::vector<MemoryRegion> parceMaps();
	std::vector<uint8_t> readMemory(uintptr_t memoryAddr, size_t size);
	bool attatch();
	bool detatch();

	void getAllNames();

};
