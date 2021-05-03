#pragma once
#include <memory>
#include <SDL.h>
#include <string>

class WindowSDL
{
public:
	WindowSDL() = default;
	~WindowSDL();

	// Create a SDL window
	bool CreateWindow();
	// Create a SDL window with stated size
	bool CreateWindow(const uint16_t _window_width, const uint16_t _window_height, const std::string& _name);

	// Destroy old and create a window with given size
	// Used for resizing on the fly
	bool RegenerateWindow(const uint16_t _window_width, const uint16_t _window_height, const std::string& _name);

	// Display window
	bool DisplayWindow();

	//TODO: Expand on this, more robust
	bool IsValid() const { return (window_ptr_ != nullptr && renderer_ptr_!= nullptr); }

	/**
	 *	\brief Get the window size stored in the object, faster
	 *	\return pair containing width and height
	 */
	std::pair<uint16_t, uint16_t> GetWindowSize() const;
	/**
	 *	\brief Get the window size stored in the directly from the window itself, only really applicable for testing
	 *	\return pair containing width and height
	 */
	std::pair<uint16_t, uint16_t> GetWindowSizeDirect() const;

	SDL_Renderer* GetRenderer() const;

private:
	//std::unique_ptr<SDL_Window> windowPtr = nullptr;
	//std::unique_ptr<SDL_Surface> ScreenSurfacePtr = nullptr;
	SDL_Window* window_ptr_ = nullptr;
	SDL_Surface* screen_surface_ptr_ = nullptr;
	SDL_Renderer* renderer_ptr_ = nullptr;

	uint16_t window_width_ = 1024;
	uint16_t window_height_ = 768;
	std::string window_name_ = "2DGame";

	bool DeleteWindow();
};
