#include "Renderer.h"

#include <algorithm>

#include "SDL_log.h"

int Renderer::CopyToBuffer(SDL_Renderer& _renderer)
{
	// Sort the elements by Z value
	if (!is_texture_info_sorted_by_z_)
	{
		std::sort(renderables_.begin(),
			renderables_.end()
			
		);
		is_texture_info_sorted_by_z_ = true;
	}

	int success = 0;
	for(auto& spriteInfoPtr: renderables_)
	{
		const SpriteInfo& info = spriteInfoPtr.lock()->sprite_info;
		
		success = SDL_RenderCopyExF(&_renderer,
			texture_handler_->GetTexture(info.image_name),
			info.src_rect,
			info.transform.GetLocationRect(),
			info.transform.GetRotation(),
			info.centre_of_rotation,
			info.transform.GetFlip()
		);

		if (success < 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to copy texture to buffer: %s", info.image_name.c_str());
			SDL_Log(SDL_GetError());
			return success;
		}
	}
	return success;
}

bool Renderer::RegisterRenderable(const Renderable& _renderable, SDL_Renderer& _renderer)
{
	// Send to the texture handler to load this texture
	texture_handler_->LoadTexture(_renderable.sprite_info.image_name, _renderer);

	// Add the renderable to our container
	renderables_.push_back(_renderable.weak_from_this());

	// Messed up the pool a little so sort it next time we render
	is_texture_info_sorted_by_z_ = false;

	return false;
}

bool Renderer::RegisterRenderable(TextRenderable& _renderable, SDL_Renderer& _renderer, std::string _text,
	Font* _font)
{
	const SDL_Color color(0x00, 0x00, 0x00, 0xFF);
	auto* surface = TTF_RenderText_Blended(_font->GetFont(), _text.c_str(), color);
	auto* texture = SDL_CreateTextureFromSurface(&_renderer, surface);

	// Create a pseudo guid for the text (means that we could create the same text but prevents using the
	// wrong image if we have different fonts for the same text)
	static uint_fast32_t guidCount;

	texture_handler_->AddTexture(_text + std::to_string(guidCount), *texture);
	
	_renderable.sprite_info.image_name = _text + std::to_string(guidCount);
	guidCount++;

	
	int w, h;
	TTF_SizeText(_font->GetFont(), _text.c_str(), &w, &h);
	_renderable.sprite_info.transform.SetSize(w, h);
	renderables_.push_back(_renderable.weak_from_this());
	
	SDL_FreeSurface(surface);

	is_texture_info_sorted_by_z_ = false;
	
	return false;
}

bool Renderer::RemoveRenderable(const std::shared_ptr<Renderable>& _renderable)
{
	if(_renderable == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Renderable passed in to RemoveRenderable was a nullptr");
		return true;
	}

	if(const auto resultIt = std::ranges::find(renderables_, _renderable); 
		resultIt !=  renderables_.end())
	{
		texture_handler_->RemoveTexture(_renderable->sprite_info.image_name);
		renderables_.erase(resultIt);
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Renderable passed in to RemoveRenderable was not found in the container");
		return true;
	}

	return false;
}

size_t Renderer::GetStoredTextureAmount() const
{
	if (texture_handler_ != nullptr)
	{
		return texture_handler_->GetTextureAmount();
	}
	return 0;
}

size_t Renderer::GetStoredTextureInfoAmount() const
{
	return renderables_.size();
}
