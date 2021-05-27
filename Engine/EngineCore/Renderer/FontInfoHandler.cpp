#include "FontInfoHandler.h"

#include <algorithm>

void FontInfoHandler::AddFontInfo(const std::shared_ptr<TextRenderable> _text_renderable)
{
	renderables_.push_back(_text_renderable);
}

bool FontInfoHandler::RemoveFontInfo(const std::shared_ptr<TextRenderable> _text_renderable)
{
	if (const auto resultIt = std::ranges::find(renderables_.cbegin(), renderables_.cend(), _text_renderable);
		resultIt != renderables_.cend())
	{
		renderables_.erase(resultIt);
		return true;
	}
	return false;
}

std::shared_ptr<TextRenderable> FontInfoHandler::GetRenderableFromName(const std::string& _renderable_name)
{
	for(auto textRenderable : renderables_)
	{
		if(textRenderable->font_info.last_image_name == _renderable_name)
		{
			return textRenderable;
		}
	}
	SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to find %s while calling FontInfoHandler::GetRenderableFromName", _renderable_name.c_str());
	return std::shared_ptr<TextRenderable>();
}

std::shared_ptr<TextRenderable> FontInfoHandler::GetFontInfo(unsigned _position)
{
	if (_position < renderables_.size())
		return renderables_.at(_position);
	return std::shared_ptr<TextRenderable>();
}

size_t FontInfoHandler::GetFontInfoAmount() const
{
	return renderables_.size();
}

void FontInfoHandler::SortFontInfo()
{
	auto pred = [](const std::shared_ptr<TextRenderable>& _a, const std::shared_ptr <TextRenderable>& _b)
	{return _a->font_info.layer == _b->font_info.layer ?
		_a->font_info.z_value < _b->font_info.z_value :
		_a->font_info.layer < _b->font_info.layer; };
	std::ranges::sort(renderables_, pred);
}
