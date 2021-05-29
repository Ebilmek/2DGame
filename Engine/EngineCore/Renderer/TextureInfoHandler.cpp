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

std::shared_ptr<Sprite> TextureInfoHandler::GetTexture(const unsigned int _position)
{
	if (_position < renderables_.size())
		return renderables_.at(_position);
	return std::shared_ptr<Sprite>();
}

size_t TextureInfoHandler::GetTextureAmount() const
{
	return renderables_.size();
}

void TextureInfoHandler::SortTextures()
{
	// Sort the elements by Z value
	auto pred = [](const std::shared_ptr<Sprite>& _a, const std::shared_ptr <Sprite>& _b)
		{return _a->sprite_info.layer == _b->sprite_info.layer ? 
			_a->sprite_info.z_value < _b->sprite_info.z_value :
			_a->sprite_info.layer < _b->sprite_info.layer; };
	std::ranges::sort(renderables_, pred);
}
