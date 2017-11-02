#include "Video.hpp"

namespace Video
{
	void Init()
	{
		if(!Core::IsInitialized())
		{
			LogWarning("tried to initialize Video before initializing Engine - initializing now");
			Core::Init();
		}
		
		if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
		{ throw SDLException("failed to initialize SDL video"); }
	}
	
	void Quit()
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}
	
	bool IsInitialized()
	{
		return SDL_WasInit(SDL_INIT_VIDEO);
	}
}