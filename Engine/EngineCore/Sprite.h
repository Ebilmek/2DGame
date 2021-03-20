#pragma once
#include <string>
#include "SDL.h"


class Sprite
{
public:
	Sprite();
	Sprite(std::string inFilePath, SDL_Renderer* inRenderer);
	~Sprite();
	
	void LoadTexture(std::string inFilePath, SDL_Renderer* inRenderer);
	
	SDL_Texture* texture;
private:
	std::string filePath;
	
};
