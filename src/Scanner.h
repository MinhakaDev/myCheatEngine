#pragma once
#include "./process.h"
#include <cstdint>
#include <cstring>
#include <vector>
#include <iostream>
#include <print>





struct MemorySnapshot
{
	uintptr_t start;
	std::vector<uint8_t> bytes;
};
class Scanner
{
	private:
		Process proc;
		std::vector<MemorySnapshot> memorySnapshot;
	public:
	Scanner();
	
	bool newScan();
	template <typename T>
	bool greaterScan(T target);
	template <typename T>
	bool exactScan(T target)
	{
		T tempValue = target;
		if (!Scanner::newScan()) 
		{
			std::println("error 1");
			return false;
		}
		std::vector<MemorySnapshot> snapshotBefore = Scanner::memorySnapshot;
		for (int i = 0; snapshotBefore.size() > i ; i++)
		{
			for (int j = 0; snapshotBefore[i].bytes.size() > j; j++) 
			{
				std::memcpy(&target, snapshotBefore[i].bytes.data() + j,sizeof(target));
				uintptr_t memoryAddr = snapshotBefore[i].start + j;
				if (tempValue == target) 
				{
					std::println("\n Memory Readed: {} at Addr = {}",target,memoryAddr);
				}
			}
		
		}
		return true;
	}
	template <typename T>
	void printScan(T target)
	{
		T value = target;
		for (int j = 0; memorySnapshot.size() > j; j++) {
		
			for (int i = 0; memorySnapshot[j].bytes.size() > i; i++) 
			{
				std::memcpy(&target, memorySnapshot[j].bytes.data(),sizeof(target));
				uintptr_t memoryAddr = memorySnapshot[j].start + i;
				std::print("\n {}		{}",memoryAddr,target);
			}
		}
	}
};





