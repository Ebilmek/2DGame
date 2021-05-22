#pragma once
#include "Sprite.h"

class TextureInfoHandler
{
public:
	void AddTexture(std::shared_ptr<Sprite> _sprite);
	bool RemoveTexture(std::shared_ptr<Sprite> _sprite);
	std::shared_ptr<Sprite> GetTexture(unsigned int _position);
	size_t GetTextureAmount() const;
	void SortTextures();
private:
	std::vector<std::shared_ptr<Sprite>> renderables_;
};