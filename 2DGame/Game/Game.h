#pragma once
#include "SDL.h"
#include "../EngineCore/WindowSDL.h"

class Game
{
public:
	Game();

	bool StartGame();

	bool StopGame();

	bool RunGame();

private:
	//std::unique_ptr<WindowSDL> WindowPtr = std::make_unique<WindowSDL>(new WindowSDL());
	std::unique_ptr<WindowSDL> WindowPtr;
	//WindowSDL* WindowPtr = new WindowSDL();
};