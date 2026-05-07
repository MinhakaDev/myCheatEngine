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
	float value = 3.14;
	std::cin >> value;
	if (sc.newExact(value))
	{
		std::println("run");
		while (value != 0) 
		{
			std::cin >> value;
			if (value == 0)
			{
				break;
			}
			if (!sc.exactValue(value)) 
			{
				return -2;
			}
			std::println("");
			sc.printScan(value);
		}

	}
	sc.write(0, value);
}
