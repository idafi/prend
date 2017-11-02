#include "Logger.hpp"

FileLogger::FileLogger(const char * const filePath)
{
	AssertPtr(filePath);
	
	file.open(filePath);
}

FileLogger::~FileLogger()
{
	file.close();
}

void FileLogger::Log(LogLevel level, const char * const msg)
{
	AssertPtr(msg);
	
	file << msg;
}