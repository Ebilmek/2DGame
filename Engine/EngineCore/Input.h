#pragma once
#include "SDL_events.h"

class Input
{
public:
	// Singleton implementation
	// Scott Meyers Effective Modern C++ better error message if the deleted functions are in public
	static Input& getInstance()
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

	void HandleEvents(const SDL_Event& event);

private:
	/* Keyboard events*/
	
	// Current mouse location
	float MouseX, MouseY;

	// Mouse delta from last poll
	float MouseDX, MouseDY;

	// Keyboard presses bitwise new update and last frame for held?
};
