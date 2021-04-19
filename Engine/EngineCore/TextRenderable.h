#pragma once
#include "Renderable.h"
#include "SDL_ttf.h"

class TextRenderable : public Renderable
{
public:
	explicit TextRenderable(const SpriteInfo& info) : Renderable(info)
	{
	}

	// TTF_SizeText to get text dimensions

	void UpdateText();
private:
	TTF_Font* font_ptr_;
};
