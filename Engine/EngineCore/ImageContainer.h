#pragma once
#include "SDL_render.h"

/*
 * Image Container
 *
 * Texture with ref count for use within the TextureHandler
 */

struct ImageContainer
{
	ImageContainer() = default;
	explicit ImageContainer(SDL_Texture* _image, const int _ref_count = 1)
		: image(_image),
		  ref_count(_ref_count)
	{
	}
	~ImageContainer()
	{
		if(ref_count <= 0)
		{
			SDL_free(image);
		}
	}

	SDL_Texture* image;
	int ref_count;
};
