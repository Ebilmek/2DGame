#pragma once
#include <unordered_map>

#include "Renderable.h"
#include "SDL_render.h"
#include "TextureHandler.h"

class Renderer
{
public:
	Renderer() = default;
	
	/**
	 *	\brief Copies the stored textures into the given renderer using the stored data
	 *
	 *	\returns SDL return from the copy if there is an error
	 */
	int CopyToBuffer(SDL_Renderer& renderer);

	bool RegisterRenderable(const Renderable& renderable, SDL_Renderer& renderer);
	bool RemoveRenderable(const std::shared_ptr<Renderable>& renderable);

	size_t GetStoredTextureAmount() const;
	size_t GetStoredTextureInfoAmount() const;
private:
	std::vector<std::weak_ptr<const Renderable>> renderables_;

	bool is_texture_info_sorted_by_z_ = false;

	std::unique_ptr<TextureHandler> texture_handler_ = std::make_unique<TextureHandler>();
};
