#pragma once

#include "Logger.hpp"

// - - - - - -
// used by the Logger to log to multiple arbitrary output destinations
// - - - - - -

class ILogger
{
	public:
		virtual ~ILogger() { }		
		virtual void Log(LogLevel level, const char * const msg) = 0;
};