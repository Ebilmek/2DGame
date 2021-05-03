#pragma once
#include "Renderable.h"
#include "Renderer.h"

namespace RenderableFactory
{
	std::shared_ptr<Renderable> CreateRenderable(const SpriteInfo& _sprite_info, SDL_Renderer& _renderer_sdl, Renderer& _renderer)
	{
		std::shared_ptr<Renderable> renderable = std::make_shared<Renderable>(_sprite_info);

		_renderer.RegisterRenderable(*renderable, _renderer_sdl);

		return renderable;
	}
}
