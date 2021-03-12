#pragma once
#include "SDL.h"
#include "../EngineCore/WindowSDL.h"

class Game
{
public:
	Game();

	bool StartGame();

	bool StopGame();

	bool RunGame(float dt);

private:
	std::unique_ptr<WindowSDL> WindowPtr;
};