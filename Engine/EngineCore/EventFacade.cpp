#include "EventFacade.h"

void EventFacade::InitializeInput(const uint16_t _screen_width, const uint16_t _screen_height)
{
	if(input_ == nullptr)
		input_ = new Input(_screen_width, _screen_height);
}
