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
	std::ranges::sort(renderables_);
}
