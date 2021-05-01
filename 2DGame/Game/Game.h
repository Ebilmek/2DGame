#pragma once
#include "Renderer.h"
#include "Sprite.h"
#include "WindowSDL.h"
#include "Transform2D.h"

class Game
{
public:
	Game();

	bool StartGame();

	bool StopGame();

	bool RunGame(const float& dt);

	bool Render(const float& dt);

	void OnWindowEvent(SDL_Event& event);

private:
	std::unique_ptr<WindowSDL> window_ptr_;

	Renderer renderer_;
	
	Transform2D transform_;
	std::shared_ptr<Sprite> sprite1_;
	std::shared_ptr<Sprite> sprite2_;
	std::shared_ptr<Sprite> sprite3_;
	float time_since_start_;

	Font* font_;
	std::shared_ptr<TextRenderable> text_;
};