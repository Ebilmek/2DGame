#include "FontHandler.h"

FontHandler::~FontHandler()
{
	for (auto& font : font_container)
	{
		delete font.second;
	}
}
