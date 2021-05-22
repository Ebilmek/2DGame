#pragma once
#include <string>

#include "InfoBase.h"
#include "RenderType.h"
#include "SDL_ttf.h"

struct FontInfo final : public InfoBase
{
	FontInfo(const Transform2D& _transform,
		std::string _text,
		std::string _font_file,
		const int _font_size,
		RenderLayer _layer = kForeground, 
		const float& _z_value = 0.0f, 
		SDL_Rect* _src_rect = nullptr, 
		SDL_FPoint* _centre_of_rotation = nullptr,
		const RenderType _render_type = RenderType::kBlended,
		const int _style = TTF_STYLE_NORMAL, 
		const SDL_Color& _text_color = SDL_Color(0x00, 0x00, 0x00, 0xFF),
		const SDL_Color& _background_color = SDL_Color(0xFF, 0xFF, 0xFF, 0xFF), 
		const int _wrap_width = 100)
		: InfoBase(_transform, _layer, _z_value, _src_rect, _centre_of_rotation),
		  text(std::move(_text)),
		  font_file(std::move(_font_file)),
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

	// 
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
