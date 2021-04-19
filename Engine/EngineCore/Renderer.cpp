#include "Renderer.h"

#include <algorithm>

#include "SDL_log.h"

int Renderer::CopyToBuffer(SDL_Renderer& renderer)
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
		
		success = SDL_RenderCopyExF(&renderer,
			texture_handler_->GetTexture(info.imageName),
			info.srcRect,
			info.transform.GetLocationRect(),
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

bool Renderer::RegisterRenderable(const Renderable& renderable, SDL_Renderer& renderer)
{
	// Send to the texture handler to load this texture
	texture_handler_->AddTexture(renderable.sprite_info.imageName, renderer);

	// Add the renderable to our container
	renderables_.push_back(renderable.weak_from_this());

	// Messed up the pool a little so sort it next time we render
	is_texture_info_sorted_by_z_ = false;

	return false;
}

bool Renderer::RegisterRenderable(TextRenderable& renderable, SDL_Renderer& renderer, std::string text,
	Font* font)
{
	const SDL_Color color(0x00, 0x00, 0x00, 0xFF);
	auto* surface = TTF_RenderText_Blended(font->GetFont(), text.c_str(), color);
	auto* texture = SDL_CreateTextureFromSurface(&renderer, surface);

	texture_handler_->AddText(text, *texture, renderer);
	
	renderable.sprite_info.imageName = text;
	int w, h;
	TTF_SizeText(font->GetFont(), text.c_str(), &w, &h);
	renderable.sprite_info.transform.SetSize(w, h);
	renderables_.push_back(renderable.weak_from_this());
	
	SDL_FreeSurface(surface);

	is_texture_info_sorted_by_z_ = false;

	// Create text with the given font

	// On success create a unique ID with text and font
	// Set spriteInfo file location to this?

	// Add it into texture pool
	
	return false;
}

bool Renderer::RemoveRenderable(const std::shared_ptr<Renderable>& renderable)
{
	if(renderable == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Renderable passed in to RemoveRenderable was a nullptr");
		return true;
	}

	if(const auto resultIt = std::ranges::find(renderables_, renderable); 
		resultIt !=  renderables_.end())
	{
		texture_handler_->RemoveTexture(renderable->sprite_info.imageName);
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
