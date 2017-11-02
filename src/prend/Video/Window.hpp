#pragma once

// - - - - - -
// Represents a program window, to which Models can be drawn
// - - - - - -

#include "Video.hpp"

namespace Video
{
	class Window
	{
		public:
			Window(char const * const name, PixelRect size);
			~Window();
			
			void Clear(Vector4 color, float depth);
			void Present();
			
			void DrawModel(const Model& model, const Material& material);
		
		private:
			SDL_Window *sdlWindow;
			SDL_GLContext glContext;
			
			void EnsureCurrent();
	};
}