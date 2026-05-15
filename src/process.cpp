#include "./process.h"
#include "ErrorReporter.h"
#include <cstddef>
#include <cstdint>
#include <print>
#include <sstream>
#include <string>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>


// constructor
Process::Process()
{
	getAllNames();
	while (true)
	{
		std::println("Please Give me the name of the process to connect: ");
		for (int i = 0; i < processNames.size();i++)
		{
			std::println("{}",processNames[i]);
		}
		std::string name;
		std::cin >> name;
		getId(name);
		if (Process::pid > 0 ) 
		{
			std::println("connected to the process {} with pid {}", name, Process::pid);
			break;
		}
		ErrorReporter::error("There is no process with this name");
		continue;
	}
}

// retrun all current process names
void Process::getAllNames()
{
	std::string path = "/proc/";
	for (const auto& proc : std::filesystem::directory_iterator(path)) 
	{
		if (!proc.is_directory()) continue;
		for(const auto& entry : std::filesystem::directory_iterator(proc.path()))
		{
			if (entry.path().filename() != "comm") continue;
			std::ifstream file(entry.path());
			if (!file.is_open()) continue;
			std::string name;
			if (std::getline(file, name)) {
				file.close();
				processNames.push_back(name);

			
			}
		}

	}

}

std::vector<std::string> Process::getProcessNames()
{
	return processNames;
}

int Process::getId(std::string procName)
{
	std::string path = "/proc/";
	for (const auto& proc : std::filesystem::directory_iterator(path)) 
	{
		if (!proc.is_directory()) continue; 
		for(const auto& entry : std::filesystem::directory_iterator(proc.path()))
		{
			if (entry.path().filename() != "comm") continue; 
			std::ifstream file(entry.path());
			if (!file.is_open()) continue;
			std::string name;
			if (std::getline(file, name)) {
				file.close();
				if (name != procName) continue;
				int procId = std::stoi(proc.path().filename().string());
				Process::pid = procId;
				return procId;
			}
		}

	}
	Process::pid = -1;
	return 0;
}


//reads the maps file that has the start and end memory of writable memory
bool Process::parceMaps()
{
	std::string path = "/proc/" + std::to_string(pid) + "/maps";
	std::ifstream file(path);
	Process::regions.clear();
	if (!file.is_open()) 
	{
		return false;
	} std::string line;
	while(std::getline(file, line)) {
		std::istringstream ss(line);
		std::string range;
		std::string perms;
		ss >> range >> perms;
		if (perms.contains("w")) {
			size_t pos = range.find("-");
			std::string start = range.substr(0 , pos);
			std::string end = range.substr(pos +1);
			MemoryRegion memory;
			memory.start = std::stoull(start, nullptr, 16);;
			memory.end = std::stoull(end, nullptr, 16);
			Process::regions.push_back(memory);

		}

	}

	return true;

}

// attatch to the process so i can read from it syscall
void Process::attatch()
{
	ptrace(PTRACE_ATTACH,pid,nullptr,nullptr);
	int status;
	waitpid(pid, &status , 0);
	Process::mem_fd = open(("/proc/" + std::to_string(pid) + "/mem").c_str(), O_RDWR);
}

// detatch from the process to resume it
void Process::detatch()
{
	ptrace(PTRACE_DETACH,pid,nullptr,nullptr);
	close(Process::mem_fd);
}

// reads from a memoryAddr of until it complete its size
std::vector<uint8_t> Process::readMemory(uintptr_t memoryAddr, size_t size)
{
	std::vector<uint8_t> buffer(size);
	pread(mem_fd, buffer.data(), size, memoryAddr);
	return buffer;
}

//write to a memoryAddr with a value
bool Process::writeMemory(uintptr_t memoryAddr,const std::vector<uint8_t>& buffer)
{
	pwrite(mem_fd, buffer.data(), buffer.size(), memoryAddr);
	return true;
}









