#pragma once
#include "Renderable.h"
#include "SDL_ttf.h"
#include "SubjectFont.h"
#include "FontInfo.h"

class TextRenderable final : public Renderable, public SubjectFont
{
public:
	explicit TextRenderable(const FontInfo& _info) :
		font_info(_info)
	{
	}
	~TextRenderable() override = default;

	void UpdateText(const std::string& _text);

	FontInfo font_info;

	// TTF_SizeText to get text dimensions
};
