#pragma once

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

	Input(Input const&) = delete;
	void operator=(Input const&) = delete;

private:
	Input() {}

public:
	// Rest of declarations ahead

	void HandleEvents();

private:
	// Current mouse location
	float MouseX, MouseY;

	// Mouse delta from last poll
	float MouseDX, MouseDY;

	// Keyboard presses bitwise new update and last frame for held?
};