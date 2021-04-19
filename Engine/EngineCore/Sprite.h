#pragma once
#include <string>

#include "Renderable.h"
#include "SDL.h"


class Sprite : public Renderable
{
public:
	explicit Sprite(const SpriteInfo& info) : Renderable(info)
	{
	}
};
