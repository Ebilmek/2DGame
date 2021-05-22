#include "TextureInfoHandler.h"

#include <algorithm>

void TextureInfoHandler::AddTexture(std::shared_ptr<Sprite> _sprite)
{
	renderables_.push_back(_sprite);
}

bool TextureInfoHandler::RemoveTexture(std::shared_ptr<Sprite> _sprite)
{
	if(const auto resultIt = std::ranges::find(renderables_.cbegin(), renderables_.cend(), _sprite);
		resultIt != renderables_.cend())
	{
		renderables_.erase(resultIt);
		return true;
	}
	return false;
}

std::shared_ptr<Sprite> TextureInfoHandler::GetTexture(unsigned int _position)
{
	return renderables_.at(_position);
}

size_t TextureInfoHandler::GetTextureAmount() const
{
	return renderables_.size();
}

void TextureInfoHandler::SortTextures()
{
	// Sort the elements by Z value
	std::ranges::sort(renderables_);
}
