#include "TextureHandler.h"

#include <functional>

#include "SDL_image.h"
#include "SDL_ttf.h"

TextureHandler::TextureHandler()
{
	const int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	const int outFlags = IMG_Init(imgFlags);
	if (outFlags != imgFlags)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "SDL_image not implemented or IMG_Init failed");
	}

	const auto sdlPtr = SDL_GetBasePath();
	if(sdlPtr == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "File path could not be retrieved, %s", SDL_GetError());
		SDL_assert(sdlPtr != nullptr);
	}
	
	file_path_ = sdlPtr;
	SDL_free(sdlPtr);

	// True Text Format initialise
	if(!TTF_WasInit())
	{
		if(TTF_Init())
		{
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "SDL_ttf could not be initialised: %s", TTF_GetError());
		}
	}
}

TextureHandler::~TextureHandler()
{
	// Make sure the pointers are deleted before cleanup
	for(auto& texture : texture_pool_)
	{
		delete texture.second;
	}

	// TODO: Make this multiple screen friendly, Quit these on application shutdown
	IMG_Quit();
	TTF_Quit();
}

void TextureHandler::AddTexture(const std::string& name, SDL_Renderer& renderer)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Adding Texture with name: %s", name.c_str());
	if (const auto textureIt = texture_pool_.find(name); textureIt != texture_pool_.end())
	{
		// Add one onto the ref count
		++textureIt->second->ref_count;
	}
	else
	{
		// Load and insert the texture
		const std::string concatFileName = file_path_ + name;
		SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Completed file path: %s", concatFileName.c_str());
		SDL_Surface* loadSurface = IMG_Load(concatFileName.c_str());
		if (loadSurface == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Image not loaded correctly: %s", concatFileName.c_str());
			SDL_Log("Error: %s", SDL_GetError());
			return;
		}
		
		SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer, loadSurface);
		if (texture == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Image not transferred correctly: %s", concatFileName.c_str());
			SDL_Log("Error: %s", SDL_GetError());
			return;
		}

		auto image = new ImageContainer(texture, 1);
		texture_pool_.insert(std::make_pair(name, image));
		
		// Free up surface;
		SDL_FreeSurface(loadSurface);
		loadSurface = nullptr;
	}
}

void TextureHandler::AddText(const std::string& name, SDL_Texture& texture, SDL_Renderer& renderer)
{
	auto image = new ImageContainer(&texture, 1);
	texture_pool_.insert(std::make_pair(name, image));
}

void TextureHandler::RemoveTexture(const std::string& name)
{
	if (auto texture = texture_pool_.find(name); 
		texture != texture_pool_.end())
	{
		// If ref count hits 0, remove the texture from the container
		--texture->second->ref_count;

		if (texture->second->ref_count <= 0)
		{
			delete texture->second;
			texture_pool_.erase(texture);
		}
	}
	else
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Trying to remove texture not currently in texture pool: %s", name.c_str());
	}
}
