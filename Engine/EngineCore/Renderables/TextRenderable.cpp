#include "TextRenderable.h"

void TextRenderable::UpdateText(const std::string& _text)
{
	font_info.text = _text;
	Notify(font_info, Event::kUpdateFont);
}