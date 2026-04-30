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
		int mem_fd;
	public:
	std::vector<MemoryRegion> regions;

	int getId(std::string name);

	bool parceMaps();
	std::vector<uint8_t> readMemory(uintptr_t memoryAddr, size_t size);
	bool writeMemory(uintptr_t memoryAddr,const std::vector<uint8_t>& buffer);

	bool attatch();
	bool detatch();

	void getAllNames();

};
