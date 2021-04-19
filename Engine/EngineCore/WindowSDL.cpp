#include "WindowSDL.h"

WindowSDL::~WindowSDL()
{
	DeleteWindow();
}

bool WindowSDL::CreateWindow()
{
	return CreateWindow(window_width_, window_height_, window_name_);
}

bool WindowSDL::CreateWindow(const uint16_t window_width, const uint16_t window_height, const std::string& name)
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) 
	{
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Could not initialise sdl2 : %s", SDL_GetError());
		return true;
	}

	if (window_ptr_ != nullptr)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_SYSTEM, "WindowPtr already initialised, possibly called unnecessarily");
		return false;
	}

	// Window setup
	window_width_ = window_width;
	window_height_ = window_height;
	window_name_ = name;
	
	window_ptr_ = SDL_CreateWindow(
		"2D Game",
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED,
		window_width, 
		window_height,
		SDL_WINDOW_SHOWN
	);

	if (window_ptr_ == nullptr) 
	{
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Could not create window: %s", SDL_GetError());
		return true;
	}

	renderer_ptr_ = SDL_CreateRenderer(window_ptr_,
		-1,
		SDL_RENDERER_ACCELERATED);

	if (renderer_ptr_ == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Could not create renderer: %s", SDL_GetError());
		return true;
	}

	return false;
}

bool WindowSDL::RegenerateWindow(const uint16_t window_width, const uint16_t window_height, const std::string& name)
{
	// @TODO: Handle errors and maybe carry this out in a better way
	DeleteWindow();

	CreateWindow(window_width, window_height, name);
	
	return false;
}

bool WindowSDL::DisplayWindow()
{
	if (window_ptr_ == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "Window was not initialised");
		return true;
	}

	screen_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
	SDL_FillRect(screen_surface_ptr_, NULL, SDL_MapRGB(screen_surface_ptr_->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window_ptr_);

	return false;
}

bool WindowSDL::DeleteWindow()
{
	if(window_ptr_ != nullptr)
	{
		SDL_DestroyWindow(window_ptr_);
		window_ptr_ = nullptr;
		// These are automatically cleaned up via destroy window
		screen_surface_ptr_ = nullptr; 
		renderer_ptr_ = nullptr;
	}

	SDL_QuitSubSystem(SDL_INIT_VIDEO);

	return false;
}

std::pair<uint16_t, uint16_t> WindowSDL::GetWindowSize() const
{
	return std::make_pair(window_width_, window_height_);
}

[[nodiscard]] std::pair<uint16_t, uint16_t> WindowSDL::GetWindowSizeDirect() const
{
	int w, h = 0;
	if (window_ptr_ != nullptr)
	{
		SDL_GetWindowSize(window_ptr_, &w, &h);
	}
	return std::make_pair(w, h);
}

SDL_Renderer* WindowSDL::GetRenderer() const
{
	if(renderer_ptr_ != nullptr)
	{
		return renderer_ptr_;
	}
	SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, 
		"Renderer not found for screen: %i (-1 indicates error with window too)", 
		SDL_GetWindowDisplayIndex(window_ptr_));
	return nullptr;
}
