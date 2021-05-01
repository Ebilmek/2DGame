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

	// TODO: Add SDL_SetColorKey support?
	// Blend mode etc.

	// TODO: BoundingBox position check
	// bool IsPositionInBoundingBox(int x, int y);
};
