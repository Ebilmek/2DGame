#pragma once
#include <memory>

#include "Sprite.h"
#include "TextRenderable.h"

class Button
{
public:
	Button(const SpriteInfo& _sprite_info, const FontInfo& _font_info);

	bool IsWithinBounds(const std::pair<float, float>& _position) const;
private:

	
	std::shared_ptr<Sprite> button_normal_;
	std::shared_ptr<Sprite> button_hover_;
	std::shared_ptr<Sprite> button_pressed_;
	std::shared_ptr<TextRenderable> text_;

	SpriteInfo button_info_;
	FontInfo text_info_;
};
