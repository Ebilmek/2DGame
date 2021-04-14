#pragma once
#include <string>
#include "SDL.h"


class Sprite
{
public:
	Sprite();
	Sprite(std::string in_file_path, SDL_Renderer* in_renderer);
	~Sprite();
	
	void LoadTexture(std::string in_file_path, SDL_Renderer* in_renderer);
	
	SDL_Texture* texture;
private:
	std::string file_path_;
	
};
