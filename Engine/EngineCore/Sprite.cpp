#include "Sprite.h"
#include "SDL_image.h"

Sprite::Sprite() : texture(nullptr)
{
}

Sprite::Sprite(std::string in_file_path, SDL_Renderer* in_renderer)
{
	LoadTexture(in_file_path, in_renderer);
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

void Sprite::LoadTexture(std::string in_file_path, SDL_Renderer* in_renderer)
{
	const int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	const int outflags = IMG_Init(imgFlags);
	if (outflags != imgFlags)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "SDL_image not implemented");
		return;
	}

	texture = nullptr;

	// Load from specified path
	SDL_Surface* loadedSurface = IMG_Load(in_file_path.c_str());
	if (loadedSurface == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Surface not created for image found at: %s", in_file_path.c_str());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(in_renderer, loadedSurface);
		if (texture == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Unable to load image found at: %s", in_file_path.c_str());
		}
	}

	SDL_FreeSurface(loadedSurface);
	loadedSurface = nullptr;
}
