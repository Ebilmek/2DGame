#pragma once
#include <memory>
#include <SDL.h>

class WindowSDL
{
public:
	WindowSDL();

	// Create a SDL window
	bool CreateWindow();
	// Create a SDL window with stated size
	bool CreateWindow(const int windowWidth, const int windowHeight);

	// Destroy old and create a window with given size
	// Used for resizing on the fly
	bool RegenerateWindow(const int windowWidth, const int windowHeight);

	// Display window
	bool DisplayWindow();

	bool DeleteWindow();

private:
	//std::unique_ptr<SDL_Window> WindowPtr = nullptr;
	//std::unique_ptr<SDL_Surface> ScreenSurfacePtr = nullptr;
	SDL_Window* WindowPtr = nullptr;
	SDL_Surface* ScreenSurfacePtr = nullptr;

	uint16_t WindowWidth = 1024;
	uint16_t WindowHeight = 768;
};