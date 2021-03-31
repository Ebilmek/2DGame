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
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Could not initialise sdl2 : %s", SDL_GetError());
		return true;
	}

	if (WindowPtr != nullptr)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_SYSTEM, "WindowPtr already initialised, possibly called unnecessarily");
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

	if (WindowPtr == nullptr) 
	{
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Could not create window: %s", SDL_GetError());
		return true;
	}

	RendererPtr = SDL_CreateRenderer(WindowPtr,
		-1,
		SDL_RENDERER_ACCELERATED);

	if (RendererPtr == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Could not create renderer: %s", SDL_GetError());
		return true;
	}

	return false;
}

bool WindowSDL::RegenerateWindow(const int windowWidth, const int windowHeight)
{
	// @TODO: Handle errors and maybe carry this out in a better way
	DeleteWindow();

	CreateWindow(windowWidth, windowHeight);
	
	return false;
}

bool WindowSDL::DisplayWindow()
{
	if (WindowPtr == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Window was not initialised");
		return true;
	}

	ScreenSurfacePtr = SDL_GetWindowSurface(WindowPtr);
	SDL_FillRect(ScreenSurfacePtr, NULL, SDL_MapRGB(ScreenSurfacePtr->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(WindowPtr);

	return false;
}

bool WindowSDL::DeleteWindow()
{
	if(ScreenSurfacePtr != nullptr)
	{
		SDL_FreeSurface(ScreenSurfacePtr);
		ScreenSurfacePtr = nullptr;
	}

	// According to SDL no need to call this, it will be done automatically
	/*if (RendererPtr != nullptr)
	{
		SDL_DestroyRenderer(RendererPtr);
		RendererPtr = nullptr;
	}*/
	
	if(WindowPtr != nullptr)
	{
		SDL_DestroyWindow(WindowPtr);
		WindowPtr = nullptr;
	}

	return false;
}

SDL_Renderer* WindowSDL::GetRenderer() const
{
	if(RendererPtr != nullptr)
	{
		return RendererPtr;
	}
	SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, 
		"Renderer not found for screen: %i (-1 indicates error with window too)", 
		SDL_GetWindowDisplayIndex(WindowPtr));
	return nullptr;
}
