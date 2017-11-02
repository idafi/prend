#include <ctime>
#include <cstdarg>
#include <chrono>

#include "Logger.hpp"

Logger Logger::defaultLogger;

Logger& Logger::Default()
{
	return defaultLogger;
}

void Logger::AddLogger(ILogger * const logger, const LogLevel minLevel)
{
	AssertPtr(logger);
	
	loggers[logger] = minLevel;
}

void Logger::RemoveLogger(ILogger * const logger)
{
	AssertPtr(logger);
	
	loggers.erase(logger);
}

void Logger::ChangeMinLevel(ILogger * const logger, const LogLevel minLevel)
{
	AssertPtr(logger);
	
	if(loggers.find(logger) != loggers.end())
	{ loggers[logger] = minLevel; }
	else
	{ LogWarning("couldn't change min level of logger: logger isn't yet registered"); }
}

void Logger::Log(const LogLevel level, char const * const msg, ...)
{
	AssertPtr(msg);
	
	if(loggers.size() > 0)
	{
		std::string str = GetTimestamp();
		str += ": ";

		char fmtMsg[512];
		va_list args;
		va_start(args, msg);
		vsnprintf(fmtMsg, 512, msg, args);

		str += fmtMsg;

		for(auto pair : loggers)
		{
			LogLevel loggerMinLevel = loggers[pair.first];
			if(level >= loggerMinLevel)
			{ pair.first->Log(level, str.c_str()); }
		}
		
		va_end(args);
	}
}

std::string Logger::GetTimestamp()
{
	using namespace std::chrono;
	
	time_point<system_clock> tp = system_clock::now();
	milliseconds ms = duration_cast<milliseconds>(tp.time_since_epoch());
	uint32 msRem = ms.count() % 1000;

	time_t time = system_clock::to_time_t(tp);
	struct tm local;
	localtime_s(&local, &time);
	
	char out[13];
	strftime(out, 9, "%T", &local);
	snprintf(out, 13, "%s.%03u", out, msRem);

	return std::string(out);
}