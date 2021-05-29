#include "Button.h"

#include "Range.h"
#include "RenderableFactory.h"

Button::Button(const SpriteInfo& _sprite_info, const FontInfo& _font_info) :
	button_info_(_sprite_info), text_info_(_font_info)
{
	// TODO: Set up changing the values for the files to load automatically
	button_normal_ = RenderableFactory::RegisterSprite(_sprite_info);
	button_hover_ = RenderableFactory::RegisterSprite(_sprite_info);
	button_pressed_ = RenderableFactory::RegisterSprite(_sprite_info);
	// TODO: Set up making this central automatically
	text_ = RenderableFactory::RegisterFontText(_font_info);
}

bool Button::IsWithinBounds(const std::pair<float, float>& _position) const
{
	const auto& info = button_info_.transform.GetLocationRect();

	// Almost always going to be a smaller area vertically (don't have to carry out second check as often)
	return SHMath::InRange(info->y, info->y + info->h, _position.second) && 
		SHMath::InRange(info->x, info->x + info->w, _position.first);
}
