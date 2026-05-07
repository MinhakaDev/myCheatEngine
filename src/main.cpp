#include "process.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <print>
#include <string>
#include "Scanner.h"

int main()
{
	Scanner sc;
	int value = 10;
	int novalue = 9;
	if (sc.newExact(value))
	{
		std::println("run");
		while (value != 0) 
		{
			std::cin >> value;
			if (!sc.exactValue(value)) 
			{
				return -2;
			}
			sc.printScan(novalue);
		}

	}
}
