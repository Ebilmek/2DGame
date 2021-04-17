#pragma once
#include "SDL_events.h"

/*
 *	Input
 *
 *	Somewhat a wrapper for SDL implementation with some extras on top
 *	Handle held buttons (start time)
 *	Maybe look into a simple combo button (button presses are recorded for set time)
 *	Mouse stuff
 */

class Input
{
public:
	// Singleton implementation
	// Scott Meyers Effective Modern C++ better error message if the deleted functions are in public
	static Input& GetInstance()
	{
		static Input instance;
		return instance;
	}

private:
	Input() {}

public:
	Input(Input const&) = delete;
	void operator=(Input const&) = delete;
	// Rest of declarations ahead

	void Initialise(const uint16_t& window_width, const uint16_t& window_height);

	void PreUpdate();
	
	void HandleEvents(const SDL_Event& event);
	void HandleKeyboardEvent(const SDL_Event& event);
	void HandleTextEditingEvent(const SDL_Event& event);
	void HandleTextInputEvent(const SDL_Event& event);
	void HandleMouseMotionEvent(const SDL_Event& event);
	void HandleMouseButtonEvent(const SDL_Event& event);
	void HandleMouseWheelEvent(const SDL_Event& event);


	/* Keyboard events*/
	
	// Current mouse location
	int mouse_x_, mouse_y_;

	// Mouse delta from last poll
	int mouse_dx_, mouse_dy_;

	// Keyboard presses bitwise new update and last frame for held?
};
