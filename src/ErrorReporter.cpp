#include "./ErrorReporter.h"
#include <iostream>




void ErrorReporter::report(Level level, std::string message)
{
	std::cerr << message << "\n";
	Entry entry;
	entry.message = message;
	entry.level = level;
	messages.push_back(entry);
}
void ErrorReporter::info(std::string msg)
{
	report(Level::Info, msg);
}
void ErrorReporter::warning(std::string msg)
{
	report(Level::Warning, msg);
}
void ErrorReporter::error(std::string msg)
{
	report(Level::Error, msg);
}

std::vector<ErrorReporter::Entry> ErrorReporter::getMessages()
{
	return messages;
}
