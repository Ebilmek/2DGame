#pragma once
#include "Renderable.h"
#include "Sprite.h"
#include "TextRenderable.h"
#include "Renderer.h"

namespace RenderableFactory
{
	std::shared_ptr<Sprite> RegisterSprite(const SpriteInfo& _sprite_info, SDL_Renderer& _renderer_sdl, Renderer& _renderer)
	{
		std::shared_ptr<Sprite> renderable = std::make_shared<Sprite>(_sprite_info);

		renderable->AddObserver(_renderer.GetTextureObserver());

		_renderer.RegisterRenderable(renderable, _renderer_sdl);

		return renderable;
	}

	std::shared_ptr<TextRenderable> RegisterFontText(const FontInfo& _font_info, SDL_Renderer& _renderer_sdl, Renderer& _renderer)
	{
		std::shared_ptr<TextRenderable> renderable = std::make_shared<TextRenderable>(_font_info);

		renderable->AddObserver(_renderer.GetFontObserver());

		_renderer.RegisterRenderable(renderable, _renderer_sdl);
		
		return renderable;
	}

	bool DeregisterSprite(std::shared_ptr<Sprite> _sprite, Renderer& _renderer)
	{
		return _renderer.RemoveRenderable(_sprite);
	}

	bool DeregisterFontText(std::shared_ptr<TextRenderable> _text, Renderer& _renderer)
	{
		// TODO: Create deregister
		return false;
	}
}
