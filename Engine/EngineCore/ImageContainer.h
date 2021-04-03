#pragma once
#include "SDL_render.h"

/*
 * Image Container
 *
 * Texture with ref count for use within the TextureHandler
 */

struct ImageContainer
{
	ImageContainer(SDL_Texture* image, int ref_count = 0)
		: image(image),
		  refCount(ref_count)
	{
	}

	SDL_Texture* image;
	int refCount;
};
