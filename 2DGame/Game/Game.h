#pragma once
#include "Renderable.h"
#include "Renderer.h"
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

	Renderer renderer;
	
	Transform2D transform;
	std::shared_ptr<Renderable> sprite1;
	std::shared_ptr<Renderable> sprite2;
	std::shared_ptr<Renderable> sprite3;
	float timeSinceStart;
};