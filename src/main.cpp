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
	if (sc.exactScan(value))
	{
		std::println("run");
	}
}
