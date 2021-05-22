#pragma once
#include "Event.h"
#include "RenderableInfo/FontInfo.h"


/*
 * ObserverFont
 *
 * Give a layer of abstraction between renderables and the renderer
 */
class ObserverFont
{
public:
	virtual ~ObserverFont() = default;
	virtual void OnNotify(FontInfo _info, Event _event) = 0;
};
