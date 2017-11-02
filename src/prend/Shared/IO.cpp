#include <fstream>
#include <sstream>
#include "Shared.hpp"

namespace IO
{
	std::string ReadFile(const std::string& filePath)
	{
		std::ifstream file(filePath, std::ifstream::in);
		if(file.good())
		{
			// just read the whole thing
			std::stringstream sstr;
			sstr << file.rdbuf();
			
			return sstr.str();
		}
		
		LogError("failed to open file '%s'", filePath.c_str());
		return std::string();
}
}