#pragma once
#include "Renderer.h"
#include "Sprite.h"
#include "StateHandler.h"
#include "WindowSDL.h"
#include "Transform2D.h"

class Game
{
public:
	Game();

	bool StartGame();

	bool StopGame();

	bool RunGame(const float& _dt);

	bool Render(const float& _dt);

	void OnWindowEvent(SDL_Event& _event);

private:
	std::unique_ptr<WindowSDL> window_ptr_;

	std::unique_ptr<StateHandler> state_handler_ = std::make_unique<StateHandler>();

	Renderer renderer_;
	
	Transform2D transform_;
	std::shared_ptr<Sprite> sprite1_;
	std::shared_ptr<Sprite> sprite2_;
	std::shared_ptr<Sprite> sprite3_;
	float time_since_start_;

	std::shared_ptr<TextRenderable> text1_;
	std::shared_ptr<TextRenderable> text2_;
	std::shared_ptr<TextRenderable> text3_;
};