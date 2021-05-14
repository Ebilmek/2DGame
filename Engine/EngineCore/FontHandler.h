#pragma once
#include <string>
#include <unordered_map>

#include "ImageContainer.h"

class FontHandler
{
public:
	~FontHandler();

	//void AddText();
	//void UpdateText();
	//void RemoveText();

private:
	std::unordered_map<std::string, ImageContainer*> font_container;
};
