#pragma once
#include <unordered_map>

#include "Renderable.h"
#include "SDL_render.h"
#include "SpriteInfo.h"
#include "TextureHandler.h"

class ImageContainer;

class Renderer
{
public:
	Renderer();
	
	// Sort then copy each
	int CopyToBuffer(SDL_Renderer* renderer);

	bool RegisterRenderable(const std::shared_ptr<Renderable>& renderable, SDL_Renderer* renderer);
	bool RemoveRenderable(const std::shared_ptr<Renderable>& renderable);

private:
	std::vector<std::weak_ptr<Renderable>> renderables;

	bool isTextureInfoSortedByZ = false;

	std::unique_ptr<TextureHandler> textureHandler = std::make_unique<TextureHandler>();
};
