#pragma once
#include "Event.h"
#include "RenderableInfo/SpriteInfo.h"


/*
 * Observer
 *
 * Give a layer of abstraction between renderables and the renderer
 */
class ObserverSprite
{
public:
	virtual ~ObserverSprite() = default;
	virtual void OnNotify(SpriteInfo _info, Event _event) = 0;
};
