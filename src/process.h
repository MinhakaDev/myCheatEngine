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
#include <print>
#include "ErrorReporter.h"

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
		std::vector<std::string> processNames;
	public:
	std::vector<MemoryRegion> regions;

	Process();
	void getAllNames();
	std::vector<std::string> getProcessNames();

	int getId(std::string name);

	bool parceMaps();
	std::vector<uint8_t> readMemory(uintptr_t memoryAddr, size_t size);
	bool writeMemory(uintptr_t memoryAddr,const std::vector<uint8_t>& buffer);

	void attatch();
	void detatch();


};
