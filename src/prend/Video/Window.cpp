#include "Video.hpp"

namespace Video
{
	Window::Window(char const * const name, const PixelRect size)
	{
		AssertPtr(name);
		AssertSign(size.Width);
		AssertSign(size.Height);
		
		// video system needs to be on for Windows to function
		if(!Video::IsInitialized())
		{
			LogWarning("tried to create Window before initializing Video - initializing now");
			Video::Init();
		}
		
		// create the window
		sdlWindow = SDL_CreateWindow(name, size.X, size.Y, size.Width, size.Height, SDL_WINDOW_OPENGL);
		
		if(!sdlWindow)
		{ throw SDLException("couldn't create SDL window"); }
		
		glContext = SDL_GL_CreateContext(sdlWindow);
		if(!glContext)
		{ throw SDLException("couldn't create GL context"); }
		
		// make sure it's current, in case another window was open
		SDL_GL_MakeCurrent(sdlWindow, glContext);
		
		GLenum glewErr = glewInit();
		if(glewErr != GLEW_OK)
		{ throw GLEWException(glewErr, "failed to initialize GLEW"); }
		
		// configure window
		SDL_GL_SetSwapInterval(1);
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);

		glViewport(0, 0, size.Width, size.Height);
	}
	
	Window::~Window()
	{
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(sdlWindow);
	}
	
	void Window::Clear(Vector4 color, float depth)
	{
		EnsureCurrent();
		
		glClearColor(color[0], color[1], color[2], color[3]);
		glClearDepth(depth);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void Window::Present()
	{
		EnsureCurrent();
		
		SDL_GL_SwapWindow(sdlWindow);
	}
	
	void Window::DrawModel(const Model& model, const Material& material)
	{
		material.Use();
		model.Draw();
	}
	
	void Window::EnsureCurrent()
	{
		AssertPtr(sdlWindow);
		AssertPtr(glContext);
		
		if(SDL_GL_GetCurrentContext() != glContext)
		{ SDL_GL_MakeCurrent(sdlWindow, glContext); }
	}
}