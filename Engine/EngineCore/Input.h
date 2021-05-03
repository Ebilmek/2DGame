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

	void Initialise(const uint16_t& _window_width, const uint16_t& _window_height);
	void ShutDown();

	// Call before event loop
	void PreUpdate();

	// Handle all SDL input events
	void HandleEvents(const SDL_Event& _event);
	
	/**
	 * \brief Check if keyboard key is pressed, only true for one frame when pressed
	 * \param _key see SDL_Scancode enumerator, uses SDL_SCANCODE_A etc.
	 * \sa SDL_Scancode
	 * \return Whether keyboard key is pressed
	 */
	bool IsKeyPressed(const uint8_t& _key);

	/**
	 * \brief Check if keyboard key is released, only true for one frame when released
	 * \param _key see SDL_Scancode enumerator, uses SDL_SCANCODE_A etc.
	 * \sa SDL_Scancode
	 * \return Whether keyboard key is pressed
	 */
	bool IsKeyReleased(const uint8_t& _key);

	/**
	 * \brief Check if keyboard key is down, if using for one frame see IsKeyPressed 
	 * \param _key see SDL_Scancode enumerator, uses SDL_SCANCODE_A etc.
	 * \sa SDL_Scancode
	 * \return Whether keyboard key is pressed
	 */
	bool IsKeyDown(const uint8_t& _key);

	/**
	 * \brief Check if mouse button is pressed, only true for one frame when pressed
	 * \param _mouse_button see SDL_Mouse defines, uses SDL_BUTTON_LEFT etc.
	 * \return Whether mouse button is pressed
	 */
	bool IsMouseButtonPressed(const int& _mouse_button);

	/**
	 * \brief Check if mouse button is released, only true for one frame when released
	 * \param _mouse_button see SDL_Mouse defines, uses SDL_BUTTON_LEFT etc.
	 * \return Whether mouse button is released
	 */
	bool IsMouseButtonReleased(const int& _mouse_button);

	/**
	 * \brief Check if mouse button is down, if using for one frame see IsMouseButtonPressed
	 * \param _mouse_button see SDL_Mouse defines, uses SDL_BUTTON_LEFT etc.
	 * \return Whether mouse button is down
	 */
	bool IsMouseButtonDown(const int& _mouse_button);

	
	/**
	 * \brief Outputs all currently pressed keys through SDL_Log.
	 * Reduced spam by only outputting when there are changes.
	 */
	void OutputAllPressedKeys();

	[[nodiscard]] std::pair<int, int> GetMousePosition() const { return mouse_position_; }

	/**
	 * \brief Retrieve mouse movement for the frame
	 * \return X & Y movement respectively
	 */
	[[nodiscard]] std::pair<int, int> GetMouseDelta() const { return mouse_delta_; }
	
	/* Keyboard events*/

private:
	// Individual event handlers
	void HandleKeyboardEvent(const SDL_Event& _event);
	void HandleTextEditingEvent(const SDL_Event& _event);
	void HandleTextInputEvent(const SDL_Event& _event);
	void HandleMouseMotionEvent(const SDL_Event& _event);
	void HandleMouseButtonEvent(const SDL_Event& _event);
	void HandleMouseWheelEvent(const SDL_Event& _event);

	// Check whether mouse_button is valid, if it's in range of the defines within SDL_Mouse
	bool IsInMouseButtonRange(const int& _mouse_button);

	// Current mouse location (first: x, second: y)
	std::pair<int, int> mouse_position_;

	// Mouse delta from last poll (first: x, second: y)
	std::pair<int, int> mouse_delta_;

	struct MouseButton
	{
		bool is_pressed;
		bool is_press_used;
	};
	
	std::unordered_map<int, MouseButton> pressed_buttons_;

	/** \brief KeySym but without packer and the scan code (now used as a key in a map)
	 *	\sa SDL_keyboard.h KeySym
	 */
	struct ReducedKeySym
	{
		int sym;
		Uint16 mod;
		bool down;
		bool hasBeenUsed;
	};

	// Keyboard presses bitwise new update and last frame for held?
	std::unordered_map<SDL_Scancode, ReducedKeySym> pressed_keys_;

	// Previous frames output log's keys, reduce spam by cutting out repeated prints
	std::string last_pressed_output_keys_;
};
