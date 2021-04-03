#include "Renderer.h"

#include <algorithm>

#include "SDL_log.h"

Renderer::Renderer()
{
	
}

int Renderer::CopyToBuffer(SDL_Renderer* renderer)
{
	// Sort the elements by Z value
	if (!isTextureInfoSortedByZ)
	{
		std::sort(renderables.begin(),
			renderables.end()
			
		);
		isTextureInfoSortedByZ = true;
	}

	int success = 0;
	for (const auto& spriteInfoPtr : renderables)
	{
		SpriteInfo& info = spriteInfoPtr.lock()->spriteInfo;
		
		success = SDL_RenderCopyExF(renderer,
			textureHandler->GetTexture(info.imageName),
			info.srcRect,
			&info.transform.GetLocationRect(),
			info.transform.GetRotation(),
			info.centreOfRotation,
			info.transform.GetFlip()
		);

		if (success < 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to copy texture to buffer: %s", info.imageName.c_str());
			SDL_Log(SDL_GetError());
			return success;
		}
	}
	return success;
}

bool Renderer::RegisterRenderable(const std::shared_ptr<Renderable>& renderable, SDL_Renderer* renderer)
{
	// Check if null pointer, shouldn't be registering nothing
	if(renderable == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Renderable passed in to RegisterRenderable was a nullptr");
		return true;
	}

	// Send to the texture handler to load this texture
	textureHandler->AddTexture(renderable->spriteInfo.imageName, renderer);

	// Add the renderable to our container
	renderables.push_back(renderable);

	// Messed up the pool a little so sort it next time we render
	isTextureInfoSortedByZ = false;

	return false;
}

bool Renderer::RemoveRenderable(const std::shared_ptr<Renderable>& renderable)
{
	if(renderable == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Renderable passed in to RemoveRenderable was a nullptr");
		return true;
	}

	auto resultIt = std::find(renderables.begin(), renderables.end(), renderable);
	if(resultIt !=  renderables.end())
	{
		textureHandler->RemoveTexture(renderable->spriteInfo.imageName);
		renderables.erase(resultIt);
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Renderable passed in to RemoveRenderable was not found in the container");
	}
}