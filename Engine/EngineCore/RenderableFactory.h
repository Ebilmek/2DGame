#pragma once
#include "Renderable.h"

std::shared_ptr<Renderable> CreateRenderable(const SpriteInfo& sprite_info, const SDL_Renderer& renderer)
{
	std::shared_ptr<Renderable> renderable = std::make_shared<Renderable>(sprite_info);

	renderer.RegisterRenderable(renderable, renderer);

	return std::move(renderable);
}
