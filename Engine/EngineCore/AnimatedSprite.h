#pragma once
#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public:
	explicit AnimatedSprite(SpriteInfo& info) : Sprite(info)
	{}

	// Update animation
	void Update();

	// Setup and store animation information
};
