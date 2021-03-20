#pragma once
#include "SDL.h"
#include "Sprite.h"
#include "WindowSDL.h"

class Game
{
public:
	Game();

	bool StartGame();

	bool StopGame();

	bool RunGame(float dt);

	bool Render(float dt);

private:
	std::unique_ptr<WindowSDL> WindowPtr;
	float position;

	Sprite sprite;
};