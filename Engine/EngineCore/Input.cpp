#include "Input.h"

#include <string>

#include "Range.h"
#include "SDL.h"

Input::Input(const uint16_t& _window_width, const uint16_t& _window_height)
{
	mouse_position_.first = _window_width / 2;
	mouse_position_.second = _window_height / 2;
	mouse_delta_.first = mouse_delta_.second = 0.0f;

	if(const int result = SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR); 
        result < 0)
	{
        SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Could not initialise SDL Input: %s", SDL_GetError());
	}
}

Input::~Input()
{
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR);
}

void Input::PreUpdate()
{
    mouse_delta_.first = 0.0f;
    mouse_delta_.second = 0.0f;

	// Remove if released greater than one frame
    erase_if(pressed_keys_, [](const auto& item) 
        {auto const& [key, value] = item;
    	return !value.down; });

	// Set a variable to say the press is more than one frame old
	for(auto& value : pressed_keys_)
	{
		if(value.second.down)
		{
            value.second.has_been_used = true;
		}
	}

    erase_if(pressed_buttons_, [](const auto& item)
        {auto const& [key, value] = item;
		return !value.is_pressed; });

    // Set a variable to say the press is more than one frame old
    for (auto& value : pressed_buttons_)
    {
        if (value.second.is_pressed)
        {
            value.second.is_press_used = true;
        }
    }
}

void Input::HandleEvents(const SDL_Event& _event)
{
	// Handle the individual inputs
	switch(_event.type)
	{
	/* Keyboard events */
	case SDL_KEYDOWN:                   /**< Key pressed */
	case SDL_KEYUP:                     /**< Key released */
        HandleKeyboardEvent(_event);
        break;
    case SDL_TEXTEDITING:               /**< Keyboard text editing (composition) */
        HandleTextEditingEvent(_event);
        break;
    case SDL_TEXTINPUT:                 /**< Keyboard text input */
        HandleTextInputEvent(_event);
        break;
    case SDL_KEYMAPCHANGED:             /**< Keymap changed due to a system event such as an
										     input language or keyboard layout change. */
        break;

    /* Mouse events */
    case SDL_MOUSEMOTION:               /**< Mouse moved */
        HandleMouseMotionEvent(_event);
        break;
    case SDL_MOUSEBUTTONDOWN:           /**< Mouse button pressed */
    case SDL_MOUSEBUTTONUP:             /**< Mouse button released */
        HandleMouseButtonEvent(_event);
        break;
    case SDL_MOUSEWHEEL:                /**< Mouse wheel motion */
        HandleMouseWheelEvent(_event);
        break;

    /* Joystick events */
    case SDL_JOYAXISMOTION:             /**< Joystick axis motion */
    case SDL_JOYBALLMOTION:             /**< Joystick trackball motion */
    case SDL_JOYHATMOTION:              /**< Joystick hat position change */
    case SDL_JOYBUTTONDOWN:             /**< Joystick button pressed */
    case SDL_JOYBUTTONUP:               /**< Joystick button released */
    case SDL_JOYDEVICEADDED:            /**< A new joystick has been inserted into the system */
    case SDL_JOYDEVICEREMOVED:          /**< An opened joystick has been removed */

    /* Game controller events */
    case SDL_CONTROLLERAXISMOTION:      /**< Game controller axis motion */
	case SDL_CONTROLLERBUTTONDOWN:      /**< Game controller button pressed */
    case SDL_CONTROLLERBUTTONUP:        /**< Game controller button released */
    case SDL_CONTROLLERDEVICEADDED:     /**< A new Game controller has been inserted into the system */
    case SDL_CONTROLLERDEVICEREMOVED:   /**< An opened Game controller has been removed */
    case SDL_CONTROLLERDEVICEREMAPPED:  /**< The controller mapping was updated */
    case SDL_CONTROLLERTOUCHPADDOWN:    /**< Game controller touchpad was touched */
    case SDL_CONTROLLERTOUCHPADMOTION:  /**< Game controller touchpad finger was moved */
    case SDL_CONTROLLERTOUCHPADUP:      /**< Game controller touchpad finger was lifted */
    case SDL_CONTROLLERSENSORUPDATE:    /**< Game controller sensor was updated */

    /* Touch events */
    case SDL_FINGERDOWN:
    case SDL_FINGERUP:
    case SDL_FINGERMOTION:

    /* Gesture events */
    case SDL_DOLLARGESTURE:
    case SDL_DOLLARRECORD:
    case SDL_MULTIGESTURE:
	default:
		break;
	}
}

bool Input::IsKeyPressed(const uint8_t& _key)
{
	// TODO: Change this so it only occurs once every time it's pressed
    if (const auto& keysIt = pressed_keys_.find(static_cast<SDL_Scancode>(_key));
        keysIt != pressed_keys_.end())
    {
        return pressed_keys_[static_cast<SDL_Scancode>(_key)].has_been_used == false && pressed_keys_[static_cast<SDL_Scancode>(_key)].down == true;
    }
    return false;
}

bool Input::IsKeyReleased(const uint8_t& _key)
{
	const auto scanCode = static_cast<SDL_Scancode>(_key);
	if (const auto& keysIt = pressed_keys_.find(scanCode);
        keysIt != pressed_keys_.end())
    {
        return pressed_keys_[scanCode].down == false;
    }
    return false;
}

bool Input::IsKeyDown(const uint8_t& _key)
{
    int numkeys;

    if(const Uint8 * keyState = SDL_GetKeyboardState(&numkeys); 
        numkeys > 0 && keyState[_key])
	{
        return true;
	}
    return false;
}

bool Input::IsMouseButtonPressed(const int& _mouse_button)
{
	if(IsInMouseButtonRange(_mouse_button))
	{
        if (const auto& buttonIt = pressed_buttons_.find(_mouse_button);
            buttonIt != pressed_buttons_.end())
        {
            return buttonIt->second.is_pressed && !buttonIt->second.is_press_used;
        }
	}
    return false;
}

bool Input::IsMouseButtonReleased(const int& _mouse_button)
{
    if (IsInMouseButtonRange(_mouse_button))
    {
	    if (const auto& buttonIt = pressed_buttons_.find(_mouse_button);
            buttonIt != pressed_buttons_.end())
        {
            return !buttonIt->second.is_pressed;
        }
    }
    return false;
}

bool Input::IsMouseButtonDown(const int& _mouse_button)
{
    if (IsInMouseButtonRange(_mouse_button))
    {
	    if(const auto& buttonIt = pressed_buttons_.find(_mouse_button); 
            buttonIt != pressed_buttons_.end())
    	{
            return buttonIt->second.is_pressed;
    	}
    }
    return false;
}

void Input::OutputAllPressedKeys()
{
    int numkeys;
    const Uint8* keyState = SDL_GetKeyboardState(&numkeys);
    std::string pressedKeys;
    int numOfPressedKeys = 0;
	
    for (int i = 0; i < numkeys; i++)
    {
        if (keyState[i] && SDL_GetScancodeName(static_cast<SDL_Scancode>(i))) // Make sure we're not adding nothing
        {
            pressedKeys += SDL_GetScancodeName(static_cast<SDL_Scancode>(i));
            pressedKeys += " ";
            numOfPressedKeys++;
        }
    }
	
    if (numOfPressedKeys > 0)
    {
    	// Member variable to keep track of keys so that we're not spamming log
    	if(pressedKeys != last_pressed_output_keys_)
    	{
            SDL_Log("Keys Pressed: %s", pressedKeys.c_str());
            last_pressed_output_keys_ = pressedKeys;
    	}
    }
}

void Input::HandleKeyboardEvent(const SDL_Event& _event)
{
    // event.key
    switch (_event.key.type)
    {
    case SDL_KEYDOWN:
        // Set up key press
        if (_event.key.repeat == 0)
        {
            ReducedKeySym currentKey;
            currentKey.sym = SDL_GetKeyFromScancode(_event.key.keysym.scancode);
            currentKey.mod = _event.key.keysym.mod;
            currentKey.down = true;
            currentKey.has_been_used = false;
            pressed_keys_.insert(std::make_pair(_event.key.keysym.scancode, currentKey));
        }
        break;
    case SDL_KEYUP:
        // Reset
        pressed_keys_[_event.key.keysym.scancode].down = false;
        break;
    default:
        break;
    }

}

void Input::HandleTextEditingEvent(const SDL_Event& _event)
{
    // event.edit
}

void Input::HandleTextInputEvent(const SDL_Event& _event)
{
    // event.text
}

void Input::HandleMouseMotionEvent(const SDL_Event& _event)
{
    // event.motion
    mouse_position_.first = _event.motion.x;
    mouse_position_.second = _event.motion.y;
    mouse_delta_.first += _event.motion.xrel;
    mouse_delta_.second += _event.motion.yrel;
}

void Input::HandleMouseButtonEvent(const SDL_Event& _event)
{
    // event.button
    // TODO: Flesh out this one
	switch (_event.button.type)
	{
	case SDL_MOUSEBUTTONDOWN:
        MouseButton mouseButton;
        mouseButton.is_press_used = false;
        mouseButton.is_pressed = true;
        pressed_buttons_.insert(std::make_pair(_event.button.button, mouseButton));
        break;
	case SDL_MOUSEBUTTONUP:
	{ // Note for self: scoped for iterator declaration
        const auto buttonIt = pressed_buttons_.find(_event.button.button);
        if (buttonIt != pressed_buttons_.end())
        {
            buttonIt->second.is_pressed = false;
        }
        else
        {
            SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Got a release of a mouse button that wasn't stored as pressed");
        }
	}
        break;
    default:
        SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Somehow got a default on MouseButtonEvent, unknown case");
        break;
	}
}

void Input::HandleMouseWheelEvent(const SDL_Event& _event)
{
    // event.wheel
}

bool Input::IsInMouseButtonRange(const int& _mouse_button)
{
    if (SHMath::InRange(SDL_BUTTON_LEFT, SDL_BUTTON_X2, _mouse_button))
    {
        return true;
    }
    SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Mouse button out of range");
    return false;
}
