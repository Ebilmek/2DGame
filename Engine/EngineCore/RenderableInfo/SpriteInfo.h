#pragma once

#include <string>

#include "InfoBase.h"

struct SpriteInfo : public InfoBase
{
	SpriteInfo(std::string _image_name,
	           const Transform2D& _transform = Transform2D(SDL_FRect({0.0f, 0.0f, 100.0f, 100.0f}), 0.0,
	                                                       SDL_FLIP_NONE),
	           RenderLayer _layer = RenderLayer::kMiddleground,
	           const float& _z_value = 0.0f,
	           SDL_Rect* _source_rect = nullptr,
	           SDL_FPoint* _centre_of_rotation = nullptr)
		: InfoBase(_transform, _layer, _z_value, _source_rect, _centre_of_rotation),
		  image_name(std::move(_image_name))
	{
	}

	std::string image_name;
};
