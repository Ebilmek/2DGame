#pragma once
#include <string>

#include "SDL_ttf.h"

class Font
{
public:
	explicit Font(const std::string file)
	{
		font_ = TTF_OpenFont(file.c_str(), 16);
	}
	~Font()
	{
		TTF_CloseFont(font_);
	}

	TTF_Font* GetFont() const { return font_; }
private:
	TTF_Font* font_;
};