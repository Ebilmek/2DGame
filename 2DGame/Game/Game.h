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

	void OnWindowEvent(SDL_Event& event);

private:
	std::unique_ptr<WindowSDL> window_ptr_;

	Renderer renderer_;
	
	Transform2D transform_;
	std::shared_ptr<Renderable> sprite1_;
	std::shared_ptr<Renderable> sprite2_;
	std::shared_ptr<Renderable> sprite3_;
	float time_since_start_;
};