#pragma once
#include "SDL_rect.h"
#include "Transform2D.h"

/**
 * Info Base
 *
 * Stores info about textures
 * Cleans up SDL pointers, so be careful of using the pointers once stored
 */
struct InfoBase
{
	explicit InfoBase(const Transform2D& _transform = Transform2D(SDL_FRect({0.0f, 0.0f, 100.0f, 100.0f}), 0.0, SDL_FLIP_NONE),
	                  const float& _z_value = 0.0f,
	                  SDL_Rect* _src_rect = nullptr,
	                  SDL_FPoint* _centre_of_rotation = nullptr) :
		transform(_transform),
		src_rect(_src_rect),
		z_value(_z_value),
		centre_of_rotation(_centre_of_rotation)
	{
	}

	virtual ~InfoBase()
	{
		delete src_rect;
		delete centre_of_rotation;
	}

	Transform2D transform;
	SDL_Rect* src_rect = nullptr;
	float z_value = 0;
	SDL_FPoint* centre_of_rotation = nullptr;
};
