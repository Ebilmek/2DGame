#include "TextureHandler.h"

#include "SDL_image.h"

#include <functional>

TextureHandler::TextureHandler()
{
	const int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	const int outFlags = IMG_Init(imgFlags);
	if (outFlags != imgFlags)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "SDL_image not implemented or IMG_Init failed");
	}
}

void TextureHandler::AddTexture(const std::string& name, SDL_Renderer* renderer)
{
	// Check if it's in the map
	auto texture = texturePool.find(name);
	if (texture != texturePool.end())
	{
		// Add one onto the ref count
		++texture->second->refCount;
	}
	else
	{
		// Load and insert the texture
		SDL_Surface* loadSurface = IMG_Load(name.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadSurface);
		// TODO: Check these above if null etc.

		auto image = new ImageContainer(texture, 1);
		texturePool.insert(std::pair<std::string, ImageContainer*>(name, image));
		
		// Free up surface;
		SDL_FreeSurface(loadSurface);
		loadSurface = nullptr;
	}
}

void TextureHandler::RemoveTexture(const std::string& name)
{
	// Check if it's in the pool
	auto texture = texturePool.find(name);
	if (texture != texturePool.end())
	{
		// If ref count hits 0, remove the texture from the container
		--texture->second->refCount;

		if (texture->second->refCount <= 0)
		{
			texturePool.erase(texture);
		}
	}
	else
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Trying to remove texture not currently in texture pool: %s", name.c_str());
	}
}
