#pragma once
#include <string>

#include "SDL_ttf.h"

class Font
{
public:
	explicit Font(const std::string _file)
	{
		font_ptr_ = TTF_OpenFont(_file.c_str(), 16);
	}
	~Font()
	{
		TTF_CloseFont(font_ptr_);
	}

	TTF_Font* GetFont() const { return font_ptr_; }

	// Set Font Style

	// Set Font Hinting

	// Set wrapped: bool, int = 1000

	// Set Render type

private:
	TTF_Font* font_ptr_;
	// Solid/Shaded/Blended
	// Whether Wrapped
	// Wrapped Width
};