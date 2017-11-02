#pragma once

// - - - - - -
// Assertions
// - - - - - -

#include <cstdarg>
#include <exception>
#include <string>

#ifdef NDEBUG

#define Assert(cond, msg) ((void)(0))
#define AssertPtr(ptr) ((void)(0))
#define AssertSign(n) ((void)(0))
#define AssertIndex(i, len) ((void)(0))
#define AssertCount(i, ct) ((void)(0))

#else

class AssertException : public std::exception
{
	public:
		AssertException(const char *msg, ...)
		{
			#define MAX_MSG_LENGTH 512
			char msgStr[MAX_MSG_LENGTH];
			
			va_list args;
			va_start(args, msg);
			vsnprintf(msgStr, MAX_MSG_LENGTH, msg, args);
			
			this->msg = std::string("!! assertion failed !!\n\t");
			this->msg += msgStr;
			
			va_end(args);
		}
		
		const char *what() const
		{
			return msg.c_str();
		}
		
	private:
		std::string msg;
};

#define Assert(cond, msg, ...) \
		if(!(cond)) \
		{ throw AssertException("%s: %s(): line %u\n\t%s", __FILE__, __func__, __LINE__, msg, ##__VA_ARGS__); } \

#define AssertPtr(ptr) Assert((ptr), "pointer '" #ptr "' is NULL")
#define AssertSign(n) Assert((n) >= 0, "value of '" #n "' is negative (%i)", n);
#define AssertIndex(i, len) Assert(((i) > -1) && ((i) < (len)), \
	"array index '" #i "' is invalid: expected greater than -1, less than %i, but got %i", len, i)
#define AssertCount(i, ct) Assert(((i) > -1) && ((i) <= (ct)), \
	"count '" #i "' is invalid: expected greater than -1, no more than %i, but got %i", ct, i)

#endif