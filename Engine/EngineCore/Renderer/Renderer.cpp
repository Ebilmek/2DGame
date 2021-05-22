#include "Renderer.h"

#include <algorithm>

#include "SDL_image.h"
#include "SDL_log.h"

int Renderer::CopyToBuffer(SDL_Renderer* _renderer)
{
	// TODO: Handle errors better, replace with a basic texture black and magenta checkboard or something of the sorts instead of throwing completely

	// Sort the elements by Z value
	texture_handler_->SortPoolByZ();
	font_handler_->SortPoolByZ();

	int success = -1;

	const int textureAmount = texture_handler_->GetPoolAmount();
	const int fontAmount = font_handler_->GetPoolAmount();
	int	textureIt = 0;
	int fontIt = 0;
	
	for (int textureCount = 0; textureCount < textureAmount + fontAmount; textureCount++)
	{
		if ((textureAmount - textureIt > 0) && (fontAmount - fontIt > 0))
		{
			// TODO: Fix this comparison when font gets sorted.
			const SpriteInfo& spriteInfo = texture_handler_->GetSpriteAt(textureIt)->sprite_info;
			const FontInfo& fontInfo = font_handler_->GetTextRenderableAt(fontIt)->font_info;

			// If texture is next
			if (static_cast<InfoBase>(spriteInfo) < static_cast<InfoBase>(fontInfo))
			{
				++textureIt;

				success = CopySpriteTexture(*_renderer, spriteInfo);
			}
			else
			{
				++fontIt;

				success = CopyFontTexture(*_renderer, fontInfo);
			}

			
		}
		else if (textureAmount - textureIt > 0)
		{
			const SpriteInfo& spriteInfo = texture_handler_->GetSpriteAt(textureIt)->sprite_info;
			++textureIt;

			success = CopySpriteTexture(*_renderer, spriteInfo);
		}
		else
		{
			const FontInfo& fontInfo = font_handler_->GetTextRenderableAt(fontIt)->font_info;
			++fontIt;

			success = CopyFontTexture(*_renderer, fontInfo);
		}

		if (success < 0)
		{
			SDL_Log(SDL_GetError());
			return success;
		}
		// reset success
		success = -1;
	}
	return success;
}

int Renderer::CopySpriteTexture(SDL_Renderer& _renderer, const SpriteInfo& _sprite_info)
{
	int success = SDL_RenderCopyExF(&_renderer,
		texture_handler_->GetTexture(_sprite_info.image_name),
		_sprite_info.src_rect,
		_sprite_info.transform.GetLocationRect(),
		_sprite_info.transform.GetRotation(),
		_sprite_info.centre_of_rotation,
		_sprite_info.transform.GetFlip()
	);

	if (success < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to copy texture to buffer: %s", _sprite_info.image_name.c_str());
	}
	return success;
}

int Renderer::CopyFontTexture(SDL_Renderer& _renderer, const FontInfo& _font_info)
{
	int success = SDL_RenderCopyExF(&_renderer,
		font_handler_->GetTexture(_font_info.image_name),
		_font_info.src_rect,
		_font_info.transform.GetLocationRect(),
		_font_info.transform.GetRotation(),
		_font_info.centre_of_rotation,
		_font_info.transform.GetFlip()
	);

	if (success < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to copy texture to buffer: %s", _font_info.image_name.c_str());
	}
	return success;
}

bool Renderer::RegisterRenderable(std::shared_ptr<Sprite> _renderable, SDL_Renderer& _renderer)
{
	return texture_handler_->RegisterRenderable(_renderable, _renderer);
}

bool Renderer::RegisterRenderable(std::shared_ptr<TextRenderable> _renderable, SDL_Renderer& _renderer)
{
	return font_handler_->RegisterRenderable(_renderable, _renderer);
}

bool Renderer::RemoveRenderable(std::shared_ptr<Sprite> _renderable)
{
	return texture_handler_->RemoveRenderable(_renderable);
}

bool Renderer::RemoveRenderable(std::shared_ptr<TextRenderable> _renderable)
{
	return font_handler_->RemoveRenderable(_renderable);
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

TextureHandler* Renderer::GetTextureObserver() const
{
	return texture_handler_;
}

FontHandler* Renderer::GetFontObserver() const
{
	return font_handler_;
}
