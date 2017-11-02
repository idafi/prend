#pragma once

// - - - - - -
// Exception for GLEW errors
// - - - - - -

#include <GL/glew.h>
#include <exception>
#include <string>

namespace Video
{
	class GLEWException : public std::exception
	{
		public:
			GLEWException(GLenum err, const char *msg)
			{
				this->msg = (msg) ? std::string(msg) : "";
				this->msg += "\n\t";
				this->msg += (const char *)(glewGetErrorString(err));
			}
			
			const char *what() const
			{
				return msg.c_str();
			}
			
		private:
			std::string msg;
	};
}