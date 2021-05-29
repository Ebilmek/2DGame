#pragma once
#include "Renderable.h"
#include "Sprite.h"
#include "TextRenderable.h"
#include "Renderer.h"
#include "RendererFacade.h"

namespace RenderableFactory
{
	inline std::shared_ptr<Sprite> RegisterSprite(const SpriteInfo& _sprite_info)
	{
		auto renderable = std::make_shared<Sprite>(_sprite_info);
		auto* renderer = RendererFacade::GetInstance().GetRenderer();
		auto* sdlRenderer = RendererFacade::GetInstance().GetSDLRenderer();

		renderable->AddObserver(renderer->GetTextureObserver());

		renderer->RegisterRenderable(renderable, *sdlRenderer);

		return renderable;
	}

	inline std::shared_ptr<TextRenderable> RegisterFontText(const FontInfo& _font_info)
	{
		auto renderable = std::make_shared<TextRenderable>(_font_info);
		auto* renderer = RendererFacade::GetInstance().GetRenderer();
		auto* sdlRenderer = RendererFacade::GetInstance().GetSDLRenderer();

		renderable->AddObserver(renderer->GetFontObserver());

		renderer->RegisterRenderable(renderable, *sdlRenderer);
		
		return renderable;
	}

	inline bool DeregisterSprite(std::shared_ptr<Sprite> _sprite)
	{
		return RendererFacade::GetInstance().GetRenderer()->RemoveRenderable(std::move(_sprite));
	}

	inline bool DeregisterFontText(std::shared_ptr<TextRenderable> _text)
	{
		return RendererFacade::GetInstance().GetRenderer()->RemoveRenderable(std::move(_text));
	}
}
