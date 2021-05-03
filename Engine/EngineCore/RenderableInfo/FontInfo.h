#pragma once
#include <string>

#include "InfoBase.h"
#include "RenderType.h"

struct FontInfo final : public InfoBase
{
	FontInfo(const Transform2D& _transform, const float& _z_value, SDL_Rect* _src_rect, SDL_FPoint* _centre_of_rotation,
		std::string _text, const int _style, const int _font_size, const SDL_Color& _text_color,
		const SDL_Color& _background_color, const int _wrap_width, const RenderType _render_type)
		: InfoBase(_transform, _z_value, _src_rect, _centre_of_rotation),
		  text(std::move(_text)),
		  style(_style),
		  font_size(_font_size),
		  text_color(_text_color),
		  background_color(_background_color),
		  wrap_width(_wrap_width),
		  render_type(_render_type)
	{
	}

	virtual ~FontInfo() = default;

	std::string text;
	// See TTF_STYLE_*
	int style;

	// Point size
	int font_size;
	SDL_Color text_color;
	
	// Shaded only
	SDL_Color background_color;
	
	// Wrap only
	int wrap_width;

	// RenderType? Solid, Shaded, Blended, Wrap
	RenderType render_type;
};
