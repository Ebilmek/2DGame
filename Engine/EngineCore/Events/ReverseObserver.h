#pragma once
#include "Event.h"
#include "RenderableInfo/InfoBase.h"


/*
 * ReverseObserver
 *
 * Flipping the observer pattern to a many subjects to one observer
 */
class ReverseObserver
{
public:
	virtual ~ReverseObserver() {}
	virtual void OnNotify(InfoBase _info, Event _event) = 0;
};
