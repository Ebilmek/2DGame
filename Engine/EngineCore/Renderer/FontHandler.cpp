#include "FontHandler.h"

#include <algorithm>

FontHandler::FontHandler()
{
	// True Text Format initialise
	if (!TTF_WasInit())
	{
		if (TTF_Init())
		{
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "SDL_ttf could not be initialised: %s", TTF_GetError());
		}
	}

	const auto sdlPtr = SDL_GetBasePath();
	if (sdlPtr == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "File path could not be retrieved, %s", SDL_GetError());
		SDL_assert(sdlPtr != nullptr);
	}

	file_path_ = sdlPtr;
	SDL_free(sdlPtr);
}

FontHandler::~FontHandler()
{
	// TODO: Make this multiple screen friendly, Quit these on application shutdown
	TTF_Quit();
}

void FontHandler::AddText(const std::string& _name, SDL_Texture& _texture)
{
	text_image_container_.insert(std::make_pair(_name, ImageContainer(&_texture)));
}

void FontHandler::RemoveText(const std::string& _name)
{
	if (auto texture = text_image_container_.find(_name);
		texture != text_image_container_.end())
	{
		// If ref count hits 0, remove the texture from the container
		--texture->second.ref_count;

		if (texture->second.ref_count <= 0)
		{
			text_image_container_.erase(texture);
		}
	}
	else
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Trying to remove texture not currently in texture pool: %s", _name.c_str());
	}
}

bool FontHandler::RegisterRenderable(std::shared_ptr<TextRenderable> _renderable, SDL_Renderer& _renderer)
{
	const SDL_Color color(0x00, 0x00, 0x00, 0xFF);

	auto* fontInfo = &_renderable->font_info;
	TTF_Font* font = TTF_OpenFont((file_path_ + fontInfo->font_file).c_str(), fontInfo->font_size);

	if(font == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Font %s not loaded correctly", fontInfo->font_file.c_str());
		return true;
	}

	auto* textTexture = CreateFontTexture(*fontInfo, font, &_renderer);

	if(textTexture == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "TextTexture %s not loaded correctly", fontInfo->text.c_str());
		return true;
	}

	// Create a pseudo guid for the text (means that we could create the same text but prevents using the
	// wrong image if we have different fonts for the same text)
	static uint_fast32_t guidCount;

	_renderable->font_info.image_name = fontInfo->text + std::to_string(guidCount);
	guidCount++;

	text_image_container_.insert(std::make_pair(fontInfo->image_name, ImageContainer(textTexture)));
	
	int w = 0, h = 0;
	TTF_SizeText(font, fontInfo->text.c_str(), &w, &h);
	_renderable->font_info.transform.SetSize(w, h);
	font_info_handler_->AddFontInfo(_renderable);

	//SDL_FreeSurface(surface);

	is_info_sorted_by_z_ = false;

	return false;
}

bool FontHandler::RemoveRenderable(std::shared_ptr<TextRenderable> _renderable)
{
	if (font_info_handler_->RemoveFontInfo(_renderable))
	{
		RemoveText(_renderable->font_info.image_name);
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Renderable passed in to RemoveRenderable was not found in the container");
		return true;
	}

	return false;
}

SDL_Texture* FontHandler::GetTexture(const std::string& _name)
{
	return text_image_container_[_name].image;
}

void FontHandler::SortPoolByZ()
{
	// Sort the elements by Z value
	if (!is_info_sorted_by_z_)
	{
		font_info_handler_->SortFontInfo();
		is_info_sorted_by_z_ = true;
	}
}

size_t FontHandler::GetPoolAmount()
{
	return font_info_handler_->GetFontInfoAmount();
}

std::shared_ptr<TextRenderable> FontHandler::GetTextRenderableAt(unsigned int _position) const
{
	return font_info_handler_->GetFontInfo(_position);
}

void FontHandler::OnNotify(FontInfo _info, const Event _event)
{
	switch (_event)
	{
	case Event::kAddFont:
		break;
	case Event::kRemoveFont:
		break;
	case Event::kUpdateFont:
		break;
	default:
		break;
	}
}

SDL_Texture* FontHandler::CreateFontTexture(FontInfo& _font_info, TTF_Font* _font, SDL_Renderer* _renderer)
{
	SDL_Surface* surface = nullptr;
	switch (_font_info.render_type)
	{
	case RenderType::kSolid:
		surface = TTF_RenderText_Solid(_font, _font_info.text.c_str(), _font_info.text_color);
		break;
	case RenderType::kShaded:
		surface = TTF_RenderText_Shaded(_font, _font_info.text.c_str(), _font_info.text_color, _font_info.background_color);
		break;
	case RenderType::kBlended:
		surface = TTF_RenderText_Blended(_font, _font_info.text.c_str(), _font_info.text_color);
		break;
	case RenderType::kWrap:
		surface = TTF_RenderText_Blended_Wrapped(_font, _font_info.text.c_str(), _font_info.text_color, _font_info.wrap_width);
		break;
	default:
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Unknown render_type used, look at FontHandler");
		break;
	}

	if(surface == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Text surface was not created correctly for %s, SDL_Error: %s", _font_info.text.c_str(), SDL_GetError());
		return nullptr;
	}

	auto* texture = SDL_CreateTextureFromSurface(_renderer, surface);
	SDL_free(surface);

	if (texture == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Text texture was not created correctly for %s, SDL_Error: %s", _font_info.text.c_str(), SDL_GetError());
		return nullptr;
	}
	
	return texture;
}
