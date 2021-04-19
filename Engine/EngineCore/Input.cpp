#include "Input.h"

#include "SDL.h"

void Input::Initialise(const uint16_t& window_width, const uint16_t& window_height)
{
	mouse_x_ = window_width / 2.0f;
	mouse_y_ = window_height / 2.0f;
	mouse_dx_ = mouse_dy_ = 0.0f;

    SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR);
}

void Input::ShutDown()
{
    SDL_QuitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR);
}

void Input::PreUpdate()
{
    mouse_dx_ = 0.0f;
    mouse_dy_ = 0.0f;
}

void Input::HandleEvents(const SDL_Event& event)
{
	// Handle the individual inputs
	switch(event.type)
	{
	/* Keyboard events */
	case SDL_KEYDOWN:
	case SDL_KEYUP:
        HandleKeyboardEvent(event);
        break;
    case SDL_TEXTEDITING:
        HandleTextEditingEvent(event);
        break;
    case SDL_TEXTINPUT:
        HandleTextInputEvent(event);
        break;
    case SDL_KEYMAPCHANGED:
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
	        
        }
        break;
    case SDL_KEYUP:
        // Reset
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
    mouse_x_ = event.motion.x;
    mouse_y_ = event.motion.y;
    mouse_dx_ += event.motion.xrel;
    mouse_dy_ += event.motion.yrel;
}

void Input::HandleMouseButtonEvent(const SDL_Event& event)
{
	// event.button
}

void Input::HandleMouseWheelEvent(const SDL_Event& event)
{
	// event.wheel
}
