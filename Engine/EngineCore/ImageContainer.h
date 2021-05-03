#pragma once
#include "SDL_render.h"

/*
 * Image Container
 *
 * Texture with ref count for use within the TextureHandler
 */

struct ImageContainer
{
	ImageContainer(SDL_Texture* _image, const int _ref_count = 0)
		: image(_image),
		  ref_count(_ref_count)
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
