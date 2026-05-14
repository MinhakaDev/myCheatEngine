#pragma once

#include <iostream>
#include <stacktrace>
#include <string>
#include <vector>

namespace ErrorReporter
{
	enum class Level {Info, Warning, Error};
	struct Entry
	{
		Level level;
		std::string message;
	};
	inline std::vector<Entry> messages;

	void report(Level level, std::string message);
	void info(std::string msg);
	void warning(std::string msg);
	void error(std::string msg);
	std::vector<Entry>getMessages();
}

