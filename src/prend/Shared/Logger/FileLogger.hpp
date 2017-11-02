#pragma once

// - - - - - -
// ILogger implementation targeting output file
// - - - - - -

#include <fstream>
#include "Logger.hpp"

class FileLogger : public ILogger
{
	public:
		FileLogger(const char * const filePath);
		~FileLogger();
		
		void Log(const LogLevel level, const char * const msg);
		
	private:
		std::ofstream file;
};