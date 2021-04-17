#pragma once
#include "SDL_render.h"

/*
 * Image Container
 *
 * Texture with ref count for use within the TextureHandler
 */

struct ImageContainer
{
	ImageContainer(SDL_Texture* image, const int ref_count = 0)
		: image(image),
		  ref_count(ref_count)
	{
	}
	~ImageContainer()
	{
		SDL_free(image);
		image = nullptr;
	}

	SDL_Texture* image;
	int ref_count;
};
