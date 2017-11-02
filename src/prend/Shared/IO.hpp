#pragma once

// - - - - - -
// IO helper functions
// - - - - - -

#include <string>
#include "Shared.hpp"

namespace IO
{
	std::string ReadFile(const std::string& filePath);
}