#pragma once
#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public:
	explicit AnimatedSprite(SpriteInfo& _info) : Sprite(_info)
	{}

	// Update animation
	void Update();

	// Setup and store animation information
};
