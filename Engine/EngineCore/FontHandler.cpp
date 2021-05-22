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

bool FontHandler::RegisterRenderable(std::shared_ptr<TextRenderable> _renderable, SDL_Renderer& _renderer)
{
	const SDL_Color color(0x00, 0x00, 0x00, 0xFF);

	// TODO: Create font from information in TextRenderable
	//auto* surface = TTF_RenderText_Blended(_font->GetFont(), _text.c_str(), color);
	//auto* texture = SDL_CreateTextureFromSurface(&_renderer, surface);

	// Create a pseudo guid for the text (means that we could create the same text but prevents using the
	// wrong image if we have different fonts for the same text)
	static uint_fast32_t guidCount;

	//AddText(_text + std::to_string(guidCount), *texture);

	//_renderable.font_info.image_name = _text + std::to_string(guidCount);
	guidCount++;


	int w = 0, h = 0;
	//TTF_SizeText(_font->GetFont(), _text.c_str(), &w, &h);
	_renderable->font_info.transform.SetSize(w, h);
	//renderables_.push_back(_renderable.weak_from_this());

	//SDL_FreeSurface(surface);

	is_info_sorted_by_z_ = false;

	return false;
}

bool FontHandler::RemoveRenderable(std::shared_ptr<TextRenderable> _renderable)
{
	// TODO: Flesh out remove text renderable
	return false;
}

SDL_Texture* FontHandler::GetTexture(const std::string& _name)
{
	return text_image_container_[_name].image;
}

void FontHandler::SortPoolByZ()
{
	// Sort the elements by Z value
	// TODO: Setup sort function
	/*if (!is_info_sorted_by_z_)
	{
		std::sort(renderables_.begin(),
			renderables_.end()
		);
		is_info_sorted_by_z_ = true;
	}*/
}

int FontHandler::GetPoolAmount()
{
	return renderables_.size();
}

std::weak_ptr<const TextRenderable> FontHandler::GetTextRenderableAt(unsigned int position)
{
	if(position < renderables_.size())
		return renderables_.at(position);
	return std::weak_ptr<const TextRenderable>();
}

void FontHandler::OnNotify(FontInfo _info, Event _event)
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
