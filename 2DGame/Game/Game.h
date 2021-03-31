#pragma once
#include "SDL.h"
#include "Sprite.h"
#include "WindowSDL.h"
#include "Transform2D.h"

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

	Transform2D transform;
	Sprite sprite;
	float timeSinceStart;
};