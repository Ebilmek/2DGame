#include "WindowSDL.h"

WindowSDL::WindowSDL()
{

}

bool WindowSDL::CreateWindow()
{
	return CreateWindow(WindowWidth, WindowHeight);
}

bool WindowSDL::CreateWindow(const int windowWidth, const int windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
		return true;
	}

	if (WindowPtr != nullptr)
	{
		fprintf(stderr, "WindowPtr already initialised");
		return false;
	}
	
	WindowPtr = SDL_CreateWindow(
		"2D Game",
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth, 
		windowHeight,
		SDL_WINDOW_SHOWN
	);

	RendererPtr = SDL_CreateRenderer(WindowPtr, 
		-1, 
		SDL_RENDERER_ACCELERATED);
	
	if (WindowPtr == nullptr) 
	{
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		return true;
	}

	return false;
}

bool WindowSDL::RegenerateWindow(const int windowWidth, const int windowHeight)
{
	return false;
}

bool WindowSDL::DisplayWindow()
{
	if (WindowPtr == nullptr)
	{
		fprintf(stderr, "Window was not initialised\n");
		return true;
	}

	ScreenSurfacePtr = SDL_GetWindowSurface(WindowPtr);
	SDL_FillRect(ScreenSurfacePtr, NULL, SDL_MapRGB(ScreenSurfacePtr->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(WindowPtr);

	return false;
}

bool WindowSDL::DeleteWindow()
{
	SDL_DestroyWindow(WindowPtr);
	WindowPtr = nullptr;


	return false;
}

SDL_Renderer* WindowSDL::GetRenderer()
{
	if(WindowPtr != nullptr)
	{
		if(RendererPtr != nullptr)
		{
			return RendererPtr;
		}
		fprintf(stderr, "Renderer not found: %s\n", SDL_GetError());
		return nullptr;
	}
	fprintf(stderr, "Window not found: %s\n", SDL_GetError());
	return nullptr;
}
