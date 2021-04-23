#include "Input.h"

#include <string>

#include "SDL.h"

void Input::Initialise(const uint16_t& window_width, const uint16_t& window_height)
{
	mouse_position_.first = window_width / 2;
	mouse_position_.second = window_height / 2;
	mouse_delta_.first = mouse_delta_.second = 0.0f;

    SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR);
}

void Input::ShutDown()
{
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR);
}

void Input::PreUpdate()
{
    mouse_delta_.first = 0.0f;
    mouse_delta_.second = 0.0f;

    erase_if(pressed_keys_, [](const auto& item) 
        {auto const& [key, value] = item;
    	return !value.down; });

	for(auto& value : pressed_keys_)
	{
		if(value.second.down)
		{
            value.second.hasBeenUsed = true;
		}
	}
}

void Input::HandleEvents(const SDL_Event& event)
{
	// Handle the individual inputs
	switch(event.type)
	{
	/* Keyboard events */
	case SDL_KEYDOWN:                   /**< Key pressed */
	case SDL_KEYUP:                     /**< Key released */
        HandleKeyboardEvent(event);
        break;
    case SDL_TEXTEDITING:               /**< Keyboard text editing (composition) */
        HandleTextEditingEvent(event);
        break;
    case SDL_TEXTINPUT:                 /**< Keyboard text input */
        HandleTextInputEvent(event);
        break;
    case SDL_KEYMAPCHANGED:             /**< Keymap changed due to a system event such as an
										     input language or keyboard layout change. */
        break;

    /* Mouse events */
    case SDL_MOUSEMOTION:               /**< Mouse moved */
        HandleMouseMotionEvent(event);
        break;
    case SDL_MOUSEBUTTONDOWN:           /**< Mouse button pressed */
    case SDL_MOUSEBUTTONUP:             /**< Mouse button released */
        HandleMouseButtonEvent(event);
        break;
    case SDL_MOUSEWHEEL:                /**< Mouse wheel motion */
        HandleMouseWheelEvent(event);
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

void Input::HandleKeyboardEvent(const SDL_Event& event)
{
    // event.key
    switch (event.key.type)
    {
	case SDL_KEYDOWN:
        // Set up key press
        if(event.key.repeat == 0)
        {
            ReducedKeySym currentKey;
            currentKey.scan_code = event.key.keysym.scancode;
        	currentKey.sym = SDL_GetKeyFromScancode(event.key.keysym.scancode);
        	currentKey.mod = event.key.keysym.mod;
            currentKey.down = true;
            currentKey.hasBeenUsed = false;
            pressed_keys_.insert(std::make_pair(event.key.keysym.scancode, currentKey));
        }
        break;
    case SDL_KEYUP:
        // Reset
        pressed_keys_[event.key.keysym.scancode].down = false;
        break;
    default:
        break;
    }
	
}

void Input::HandleTextEditingEvent(const SDL_Event& event)
{
	// event.edit
}

void Input::HandleTextInputEvent(const SDL_Event& event)
{
	// event.text
}

void Input::HandleMouseMotionEvent(const SDL_Event& event)
{
	// event.motion
    mouse_position_.first = event.motion.x;
    mouse_position_.second = event.motion.y;
    mouse_delta_.first += event.motion.xrel;
    mouse_delta_.second += event.motion.yrel;
}

void Input::HandleMouseButtonEvent(const SDL_Event& event)
{
	// event.button
    // TODO: Flesh out this one
}

void Input::HandleMouseWheelEvent(const SDL_Event& event)
{
	// event.wheel
}

bool Input::IsKeyPressed(const uint8_t& key)
{
	// TODO: Change this so it only occurs once every time it's pressed
    if (auto keysIt = pressed_keys_.find(static_cast<SDL_Scancode>(key));
        keysIt != pressed_keys_.end())
    {
        return pressed_keys_[static_cast<SDL_Scancode>(key)].hasBeenUsed == false && pressed_keys_[static_cast<SDL_Scancode>(key)].down == true;
    }
    return false;
}

bool Input::IsKeyReleased(const uint8_t& key)
{
	const auto scanCode = static_cast<SDL_Scancode>(key);
	if (const auto keysIt = pressed_keys_.find(scanCode);
        keysIt != pressed_keys_.end())
    {
        return pressed_keys_[scanCode].down == false;
    }
    return false;
}

bool Input::IsKeyDown(const uint8_t& key)
{
    int numkeys;

    if(const Uint8 * keyState = SDL_GetKeyboardState(&numkeys); 
        numkeys > 0 && keyState[key])
	{
        return true;
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
