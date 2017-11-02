#pragma once

// - - - - - -
// multi-target logging system
// - - - - - -

#include <map>
#include <string>
#include "../Shared.hpp"
#include "LogLevel.hpp"
#include "ILogger.hpp"

class Logger
{
	public:
		static Logger& Default();
	
		void AddLogger(ILogger * const logger, const LogLevel minLevel);
		void RemoveLogger(ILogger * const logger);
		void ChangeMinLevel(ILogger * const logger, const LogLevel minLevel);
		
		void Log(LogLevel level, char const * const msg, ...);
		
	private:
		static Logger defaultLogger;
		
		std::map<ILogger * const, LogLevel> loggers;
		
		std::string GetTimestamp();
};

#define LogDebug(msg, ...) Logger::Default().Log(LOG_DEBUG, msg "\n", ##__VA_ARGS__)
#define LogNote(msg, ...) Logger::Default().Log(LOG_NOTE, msg "\n", ##__VA_ARGS__)
#define LogWarning(msg, ...) Logger::Default().Log(LOG_WARNING, msg "\n", ##__VA_ARGS__)
#define LogError(msg, ...) Logger::Default().Log(LOG_ERROR, msg "\n", ##__VA_ARGS__)
#define LogFailure(msg, ...) Logger::Default().Log(LOG_FAILURE, msg "\n", ##__VA_ARGS__)

#include "ConsoleLogger.hpp"
#include "FileLogger.hpp"