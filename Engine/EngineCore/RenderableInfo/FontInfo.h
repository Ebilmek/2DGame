#pragma once
#include <string>

#include "InfoBase.h"
#include "RenderType.h"

struct FontInfo final : public InfoBase
{
	FontInfo(const Transform2D& _transform, RenderLayer _layer, const float& _z_value, SDL_Rect* _src_rect, SDL_FPoint* _centre_of_rotation,
		std::string _text, std::string _font_file, const RenderType _render_type, const int _style, const int _font_size, const SDL_Color& _text_color,
		const SDL_Color& _background_color, const int _wrap_width)
		: InfoBase(_transform, _layer, _z_value, _src_rect, _centre_of_rotation),
		  text(std::move(_text)),
		  font_file(std::move(_font_file)),
		  render_type(_render_type),
		  style(_style),
		  font_size(_font_size),
		  text_color(_text_color),
		  background_color(_background_color),
		  wrap_width(_wrap_width)
	{
	}

	virtual ~FontInfo() = default;

	std::string text;

	std::string image_name;

	// File location from Assets
	std::string font_file;

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
