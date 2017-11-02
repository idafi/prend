#include "Core.hpp"

namespace Core
{
	void Init()
	{
		if(SDL_Init(SDL_INIT_EVENTS) < 0)
		{ throw SDLException("failed to initialize SDL"); }
	}
	
	void Quit()
	{
		SDL_Quit();
	}
	
	bool IsInitialized()
	{
		return SDL_WasInit(SDL_INIT_EVENTS);
	}
}