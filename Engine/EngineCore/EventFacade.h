#pragma once
#include "Input.h"

/**
 *	Event Facade
 *
 *	Not too keen on the name, but wanted to give it a better name than facade.
 *	Singleton class that deals with the creation and deletion of large "omnipresent"
 *	classes such as Input and Internal Events (none SDL ones that will probably be
 *	added later but at the time of writing this is not implemented and I'll probably
 *	forget to edit this). Attempt is to reduce singletons (because they're apparently evil,
 *	but they make sense here)
 *
 *	TODO: Split this up so only certain modules are initialised by calling initialise(modules)
 */
class EventFacade
{
public:
	// Singleton implementation
	// Scott Meyers Effective Modern C++ better error message if the deleted functions are in public
	static EventFacade& GetInstance()
	{
		static EventFacade instance;
		return instance;
	}

private:
	EventFacade() = default;
	~EventFacade() { delete input_; }
public:
	EventFacade(EventFacade const&) = delete;
	void operator=(EventFacade const&) = delete;

	/* Rest of implementation */
	void InitializeInput(const uint16_t _screen_width, const uint16_t _screen_height);
	[[nodiscard]] Input* GetInput() const { return input_; }
private:
	Input* input_ = nullptr;
};