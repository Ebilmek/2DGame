#pragma once
#include <string>

#include "Renderable.h"
#include "SDL.h"
#include "SpriteInfo.h"
#include "SubjectSprite.h"


class Sprite : public Renderable, public SubjectSprite
{
public:
	Sprite(const SpriteInfo& _info) : sprite_info(_info)
	{
	}
	virtual ~Sprite() = default;

	SpriteInfo sprite_info;

	// TODO: Add SDL_SetColorKey support?
	// Blend mode etc.

	// TODO: BoundingBox position check
	// bool IsPositionInBoundingBox(int x, int y);
};
