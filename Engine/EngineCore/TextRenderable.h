#pragma once
#include "Renderable.h"
#include "SDL_ttf.h"

class TextRenderable final : public Renderable
{
public:
	explicit TextRenderable(const SpriteInfo& _info) :
		Renderable(_info)
	{
	}

	// TTF_SizeText to get text dimensions
};
