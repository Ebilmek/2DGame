#include "TextureHandler.h"

#include <algorithm>
#include <functional>

#include "SDL_image.h"
#include "SDL_ttf.h"

TextureHandler::TextureHandler()
{
	const int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (const int outFlags = IMG_Init(imgFlags); 
		outFlags != imgFlags)
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
}

TextureHandler::~TextureHandler()
{
	// TODO: Make this multiple screen friendly, Quit these on application shutdown
	IMG_Quit();
}

void TextureHandler::LoadTexture(const std::string& name, SDL_Renderer& _renderer)
{
	SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Adding Texture with name: %s", name.c_str());
	if (const auto textureIt = texture_pool_.find(name); textureIt != texture_pool_.end())
	{
		// Add one onto the ref count
		++textureIt->second.ref_count;
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
		
		SDL_Texture* texture = SDL_CreateTextureFromSurface(&_renderer, loadSurface);
		if (texture == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Image not transferred correctly: %s", concatFileName.c_str());
			SDL_Log("Error: %s", SDL_GetError());
			return;
		}

		texture_pool_.insert(std::make_pair(name, ImageContainer(texture)));
		
		// Free up surface;
		SDL_FreeSurface(loadSurface);
		loadSurface = nullptr;
	}
}

bool TextureHandler::RegisterRenderable(std::shared_ptr<Sprite> _renderable, SDL_Renderer& _renderer)
{
	// Send to the texture handler to load this texture
	LoadTexture(_renderable->sprite_info.image_name, _renderer);

	// Add the renderable to our container
	renderables_.push_back(_renderable);

	// Messed up the pool a little so sort it next time we render
	is_info_sorted_by_z_ = false;

	return false;
}

void TextureHandler::RemoveTexture(const std::string& _name)
{
	if (auto texture = texture_pool_.find(_name); 
		texture != texture_pool_.end())
	{
		// If ref count hits 0, remove the texture from the container
		--texture->second.ref_count;

		if (texture->second.ref_count <= 0)
		{
			texture_pool_.erase(texture);
		}
	}
	else
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Trying to remove texture not currently in texture pool: %s", _name.c_str());
	}
}

bool TextureHandler::RemoveRenderable(std::shared_ptr<Sprite> _renderable)
{
	if (const auto resultIt = std::ranges::find(renderables_.cbegin(), renderables_.cend(), _renderable);
		resultIt != renderables_.cend())
	{
		RemoveTexture((*resultIt)->sprite_info.image_name);
		renderables_.erase(resultIt);
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Renderable passed in to RemoveRenderable was not found in the container");
		return true;
	}

	return false;
}

void TextureHandler::SortPoolByZ()
{
	// Sort the elements by Z value
	if (!is_info_sorted_by_z_)
	{
		std::sort(renderables_.begin(),
			renderables_.end()
		);
		is_info_sorted_by_z_ = true;
	}
}

size_t TextureHandler::GetPoolAmount() const
{
	return renderables_.size();
}

std::shared_ptr<Sprite> TextureHandler::GetSpriteAt(unsigned int _position)
{
	return renderables_.at(_position);
}

void TextureHandler::OnNotify(SpriteInfo _info, const Event _event)
{
	switch (_event)
	{
	case Event::kAddTexture:
		break;
	case Event::kRemoveTexture:
		//RemoveTexture();
		break;
	case Event::kUpdateTexture:
		break;
	default:
		break;
	}
}
