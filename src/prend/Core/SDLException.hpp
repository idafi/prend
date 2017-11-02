#pragma once

// - - - - - -
// Exception for SDL errors
// - - - - - -

#include <exception>
#include <string>
#include "Core.hpp"

namespace Core
{
	class SDLException : public std::exception
	{
		public:
			SDLException(const char *msg)
			{
				this->msg = (msg) ? std::string(msg) : "";
				this->msg += "\n\t";
				this->msg += SDL_GetError();
			}
			
			const char *what() const
			{
				return msg.c_str();
			}
			
		private:
			std::string msg;
	};
}