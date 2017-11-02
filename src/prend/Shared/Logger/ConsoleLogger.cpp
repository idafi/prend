#include "Logger.hpp"

ConsoleLogger::ConsoleLogger()
{
	console = new Console();
}

ConsoleLogger::~ConsoleLogger()
{
	delete console;
}

void ConsoleLogger::Log(const LogLevel level, const char * const msg)
{
	AssertPtr(msg);
	
	SetLevelColor(level);
	console->Print(msg);
}

void ConsoleLogger::SetLevelColor(const LogLevel level)
{
	switch(level)
	{
		case LOG_DEBUG:
			console->SetColor(CONSOLE_GREY, CONSOLE_BLACK);
			break;
		case LOG_NOTE:
			console->SetColor(CONSOLE_WHITE, CONSOLE_BLACK);
			break;
		case LOG_WARNING:
			console->SetColor(CONSOLE_YELLOW, CONSOLE_BLACK);
			break;
		case LOG_ERROR:
			console->SetColor(CONSOLE_RED, CONSOLE_BLACK);
			break;
		case LOG_FAILURE:
			console->SetColor(CONSOLE_YELLOW, CONSOLE_RED);
			break;
	}
}