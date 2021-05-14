#pragma once
#include "RenderLayer.h"
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
	explicit InfoBase(const Transform2D& _transform = Transform2D(SDL_FRect({ 0.0f, 0.0f, 100.0f, 100.0f }), 0.0, SDL_FLIP_NONE),
	                  const RenderLayer _layer = RenderLayer::kMiddleground,
	                  const float& _z_value = 0.0f,
	                  SDL_Rect* _src_rect = nullptr,
	                  SDL_FPoint* _centre_of_rotation = nullptr) :
		transform(_transform),
		src_rect(_src_rect),
		layer(_layer),
		z_value(_z_value),
		centre_of_rotation(_centre_of_rotation)
	{
	}

	virtual ~InfoBase()
	{
		delete src_rect;
		delete centre_of_rotation;
	}

	RenderLayer layer;
	Transform2D transform;
	SDL_Rect* src_rect = nullptr;
	float z_value = 0; // Could be some weight or some calculated value, but not really necessary in this project so just an arbitrary float value.
	SDL_FPoint* centre_of_rotation = nullptr;
};
