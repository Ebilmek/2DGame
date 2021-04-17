#pragma once
#include "Renderable.h"
#include "Renderer.h"

namespace RenderableFactory
{
	std::shared_ptr<Renderable> CreateRenderable(const SpriteInfo& sprite_info, SDL_Renderer& renderer_sdl, Renderer& renderer)
	{
		std::shared_ptr<Renderable> renderable = std::make_shared<Renderable>(sprite_info);

		renderer.RegisterRenderable(*renderable, renderer_sdl);

		return renderable;
	}
}
