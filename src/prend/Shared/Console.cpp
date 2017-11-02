#if defined(_WIN64) || defined(_WIN32)

#include <cstdio>
#include <stdexcept>
#include <windows.h>
#include "Shared.hpp"

uint16 Console::GetForegroundColor(ConsoleColor color)
{
	switch(color)
	{
		case CONSOLE_BLACK:
			return 0;
		case CONSOLE_GREY:
			return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		case CONSOLE_WHITE:
			return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		case CONSOLE_RED:
			return FOREGROUND_RED | FOREGROUND_INTENSITY;
		case CONSOLE_YELLOW:
			return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	}
	
	return 0;
}

uint16 Console::GetBackgroundColor(ConsoleColor color)
{
	switch(color)
	{
		case CONSOLE_BLACK:
			return 0;
		case CONSOLE_GREY:
			return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		case CONSOLE_WHITE:
			return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		case CONSOLE_RED:
			return BACKGROUND_RED | BACKGROUND_INTENSITY;
		case CONSOLE_YELLOW:
			return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
	}
	
	return 0;
}

Console::Console()
{
	if(!AllocConsole())
	{ throw std::runtime_error("failed to allocate console"); }
	
	// we need an extant but otherwised-unused file to satisfy freopen_s
	freopen_s(&dummy, "CONIN$", "r", stdin);
	freopen_s(&dummy, "CONOUT$", "w", stdout);
	freopen_s(&dummy, "CONOUT$", "w", stderr);
}

Console::~Console()
{
	fclose(dummy);
	FreeConsole();
}

void Console::SetColor(ConsoleColor foreground, ConsoleColor background)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD color = GetForegroundColor(foreground) | GetBackgroundColor(background);
	
	SetConsoleTextAttribute(hConsole, color);
}

void Console::Print(const char * const msg)
{
	AssertPtr(msg);
	
	// we could write directly... or we could make it easy and printf.
	printf("%s", msg);
}
#endif