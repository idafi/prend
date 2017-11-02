#pragma once

// - - - - - -
// platform-independent console interface
// - - - - - -

#include <cstdio>
#include "Shared.hpp"

enum ConsoleColor
{
	CONSOLE_BLACK,
	CONSOLE_GREY,
	CONSOLE_WHITE,
	CONSOLE_RED,
	CONSOLE_YELLOW
};

class Console
{
	public:
		Console();
		~Console();
		
		void SetColor(ConsoleColor foreground, ConsoleColor background);
		void Print(const char * const msg);
		
	private:
		FILE *dummy;
		
		uint16 GetForegroundColor(ConsoleColor color);
		uint16 GetBackgroundColor(ConsoleColor color);
};