#pragma once
#include "TextRenderable.h"

class FontInfoHandler
{
public:
	void AddFontInfo(std::shared_ptr<TextRenderable> _text_renderable);
	bool RemoveFontInfo(std::shared_ptr<TextRenderable> _text_renderable);
	std::shared_ptr<TextRenderable> GetFontInfo(unsigned int _position);
	size_t GetFontInfoAmount() const;
	void SortFontInfo();
private:
	std::vector<std::shared_ptr<TextRenderable>> renderables_;
};
