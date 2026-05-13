#pragma once
#include "./process.h"
#include <cstdint>
#include <cstring>
#include <fstream>
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
		std::vector<uintptr_t> memoryAddrList;
	public:
	Scanner();
	

	template <typename T>
	bool scanExact(T target)
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
					Scanner::memoryAddrList.push_back(memoryAddr);
				}
			}
		
		}
		return true;
	}

	template <typename T>
	bool rescanExact(T target)
	{
		T tempValue = target;
		std::vector<uintptr_t> newMemoryAddrList;
		Scanner::proc.attatch();
		for (int i = 0; Scanner::memoryAddrList.size() > i; i++) 
		{
			T value = readValue<T>(memoryAddrList[i]);
			if (tempValue == value) 
			{
				newMemoryAddrList.push_back(Scanner::memoryAddrList[i]);
			}
		}
		Scanner::proc.detatch();
		Scanner::memoryAddrList = newMemoryAddrList;
		return true;
	}
	
	template<typename T>
	bool rescanGreater(T target)
	{
		T tempValue = target;
		std::vector<uintptr_t> newMemoryAddrList;
		if(!newScan())
		{
			std::println("error 3");
			return false;
		}
		Scanner::proc.attatch();
		for (int i = 0; Scanner::memoryAddrList.size() > i; i++) 
		{
			std::vector<uint8_t> value = Scanner::proc.readMemory(Scanner::memoryAddrList[i], sizeof(target));

			std::memcpy(&target,value.data(), sizeof(target));
			if (target > tempValue) 
			{
				newMemoryAddrList.push_back(Scanner::memoryAddrList[i]);
			}
		}
		proc.detatch();
		memoryAddrList = newMemoryAddrList;
		return true;
	}
	template<typename T>

	bool rescanLower()
	{
		return true;
	}
	template<typename T>

	bool rescanSame()
	{
		return true;
	}

	template <typename T>
	void write(int index, T value)
	{
		std::vector<uint8_t> data(sizeof(T));
		std::memcpy(data.data(), &value, sizeof(T));
		Scanner::proc.attatch();
		proc.writeMemory(Scanner::memoryAddrList[index], data);
		Scanner::proc.detatch();
	}

	template <typename T>
	void printScan(T target)
	{
		T value = target;
		Scanner::proc.attatch();
		for (int i = 0; Scanner::memoryAddrList.size() > i; i++) 
		{
			std::vector<uint8_t> value = Scanner::proc.readMemory(Scanner::memoryAddrList[i], sizeof(target));
			std::memcpy(&target,value.data(), sizeof(target));
			std::print("\n [{}] {}		{}",i,Scanner::memoryAddrList[i],target);
		}
		Scanner::proc.detatch();

	}
	template <typename T>
	T getMemoryValue(uintptr_t memoryAddr)
	{
		T target;
		Scanner::proc.attatch();
		std::vector<uint8_t> value = Scanner::proc.readMemory(memoryAddr, sizeof(T));
		Scanner::proc.detatch();
		std::memcpy(&target,value.data(),sizeof(target));
		return target;
	}
	template <typename T>
	T readValue(uintptr_t memoryAddr)
	{
		T target;
		std::vector<uint8_t> value = Scanner::proc.readMemory(memoryAddr, sizeof(T));
		std::memcpy(&target,value.data(),sizeof(target));
		return target;
	}

	bool newScan();
	std::vector<uintptr_t> getMemoryAddrList();
};





