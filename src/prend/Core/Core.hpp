#pragma once

// - - - - - -
// Core system entry point
// - - - - - -

#include <SDL.h>
#include "../Shared/Shared.hpp"
#include "SDLException.hpp"

namespace Core
{
	void Init();
	void Quit();
	bool IsInitialized();
}