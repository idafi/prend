#pragma once

// - - - - - -
// ILogger implementation targeting program console
// - - - - - -

#include "Logger.hpp"

class ConsoleLogger : public ILogger
{
	public:
		ConsoleLogger();
		~ConsoleLogger();
		
		void Log(const LogLevel level, const char * const msg);
		
	private:
		Console *console;
		
		void SetLevelColor(const LogLevel level);
};