#pragma once
#include "Renderer.h"
#include "Sprite.h"
#include "StateHandler.h"
#include "Transform2D.h"
#include "WindowSDL.h"

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
	void FpsCount(const float& _dt);
	
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

	std::shared_ptr<Sprite> cursor1_;

	std::shared_ptr<Sprite> image1_;
	std::shared_ptr<Sprite> image2_;
	std::shared_ptr<Sprite> image3_;
	std::shared_ptr<Sprite> image4_;

	// Simple FPS counter for testing
	std::shared_ptr<TextRenderable> fps_counter_text_;
	float fps_counter_ = 0.0f;
	int frame_count_ = 0;
};