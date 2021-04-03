#pragma once

#include <string>

#include "SDL_rect.h"
#include "SDL_render.h"
#include "Transform2D.h"

struct SpriteInfo
{
	SpriteInfo(std::string image_name,
		const Transform2D& transform = Transform2D(SDL_FRect({ 0.0f,0.0f,100.0f,100.0f }), 0.0, SDL_FLIP_NONE),
		const float& z_value = 0.0f,
		SDL_Rect* src_rect = nullptr,
		SDL_FPoint* centre_of_rotation = nullptr)
		: imageName(std::move(image_name)),
		  transform(transform),
		  srcRect(src_rect),
		  zValue(z_value),
		  centreOfRotation(centre_of_rotation)
	{
	}

	std::string imageName;
	Transform2D transform;
	SDL_Rect* srcRect;
	float zValue;
	SDL_FPoint* centreOfRotation;
};
