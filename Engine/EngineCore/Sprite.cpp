#include "Sprite.h"
#include "SDL_image.h"

Sprite::Sprite() : texture(nullptr)
{
}

Sprite::Sprite(std::string inFilePath, SDL_Renderer* inRenderer)
{
	LoadTexture(inFilePath, inRenderer);
}

Sprite::~Sprite()
{
	if(texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	IMG_Quit();
}

void Sprite::LoadTexture(std::string inFilePath, SDL_Renderer* inRenderer)
{
	const int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	const int outflags = IMG_Init(imgFlags);
	if (outflags != imgFlags)
	{
		fprintf(stderr, "SDL_image not implemented");
		return;
	}

	texture = nullptr;

	// Load from specified path
	SDL_Surface* loadedSurface = IMG_Load(inFilePath.c_str());
	if (loadedSurface == nullptr)
	{
		// throw error
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(inRenderer, loadedSurface);
		if (texture == nullptr)
		{
			// throw error
		}
	}

	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;
}
