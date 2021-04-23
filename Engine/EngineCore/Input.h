#pragma once
#include <unordered_map>
#include <utility>

#include "SDL_events.h"

/*
 *	Input
 *
 *	Somewhat a wrapper for SDL implementation with some extras on top
 *	Handle held buttons (start time)
 *	Maybe look into a simple combo button (button presses are recorded for set time)
 *	Mouse stuff
 */

// KeySym but without packer
struct ReducedKeySym
{
	SDL_Scancode scan_code;
	int sym;
	Uint16 mod;
	bool down;
	bool hasBeenUsed;
};

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
	void ShutDown();

	// Call before event loop
	void PreUpdate();
	
	void HandleEvents(const SDL_Event& event);
	void HandleKeyboardEvent(const SDL_Event& event);
	void HandleTextEditingEvent(const SDL_Event& event);
	void HandleTextInputEvent(const SDL_Event& event);
	void HandleMouseMotionEvent(const SDL_Event& event);
	void HandleMouseButtonEvent(const SDL_Event& event);
	void HandleMouseWheelEvent(const SDL_Event& event);

	bool IsKeyPressed(const uint8_t& key);

	bool IsKeyReleased(const uint8_t& key);

	bool IsKeyDown(const uint8_t& key);

	void OutputAllPressedKeys();

	[[nodiscard]] std::pair<int, int> GetMousePosition() const { return mouse_position_; }
	[[nodiscard]] std::pair<int, int> GetMouseDelta() const { return mouse_delta_; }
	/* Keyboard events*/

private:
	// Current mouse location (first: x, second: y)
	std::pair<int, int> mouse_position_;
	
	// Mouse delta from last poll (first: x, second: y)
	std::pair<int, int> mouse_delta_;

	// Keyboard presses bitwise new update and last frame for held?
	std::unordered_map<SDL_Scancode, ReducedKeySym> pressed_keys_;

	std::string last_pressed_output_keys_;
};
