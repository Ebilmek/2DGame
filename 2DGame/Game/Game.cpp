#include "Game.h"

#include <string>
#include <cmath>

#include "SDL_rect.h"
#include "SHDebug.h"
#include "Input.h"

Game::Game() : window_ptr_(new WindowSDL()),
	transform_(SDL_FRect({ 100.f, 100.f, 64.f, 64.f })),
	sprite1_(std::make_shared<Renderable>(std::string(R"(Assets\Images\ball.jpg)"))),
	sprite2_(std::make_shared<Renderable>(std::string(R"(Assets\Images\ball.jpg)"))), 
	sprite3_(std::make_shared<Renderable>(std::string(R"(Assets\Images\gear.png)"))),
	time_since_start_(0.0f)
{
	//windowPtr = std::make_unique<WindowSDL>();
	sprite2_->spriteInfo.transform.Translate(150.0f, 0.0f);
	sprite3_->spriteInfo.transform.Translate(300.0f, 0.0f);
}

bool Game::StartGame()
{
	window_ptr_->CreateWindow();
	window_ptr_->DisplayWindow();

	const auto shRenderer = window_ptr_->GetRenderer();
	renderer_.RegisterRenderable(*sprite1_, *shRenderer);
	renderer_.RegisterRenderable(*sprite2_, *shRenderer);
	renderer_.RegisterRenderable(*sprite3_, *shRenderer);

	// Initialise input
	Input* inputHandler = &Input::GetInstance();
	const auto windowSize = window_ptr_->GetWindowSize();
	inputHandler->Initialise(windowSize.first, windowSize.second);
	inputHandler = nullptr;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	return false;
}

bool Game::StopGame()
{
	if (window_ptr_)
	{
		window_ptr_->DeleteWindow();
		window_ptr_ = nullptr;
	}
	return false;
}

bool Game::RunGame(const float dt)
{
	SDL_Event event;
	Input* inputHandler = &Input::GetInstance();

	inputHandler->PreUpdate();

	// Exit clause
	// @TODO: replace with input variant	
	int numkeys;
	const Uint8* keyState = SDL_GetKeyboardState(&numkeys);
	
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		SDL_Event quit;
		quit.type = SDL_QUIT;
		SDL_PushEvent(&quit);
	}
	
	// Event loop
	// TODO: Could multi-thread this, each event type could have its own thread
	while(SDL_PollEvent(&event))
	{
		if (event.type > SDL_KEYDOWN && event.type < SDL_MULTIGESTURE)
		{
			inputHandler->HandleEvents(event);
			continue;
		}

		switch(event.type)
		{
		case SDL_WINDOWEVENT:
			OnWindowEvent(event);
			break;
		case SDL_QUIT:
			StopGame();
			return true;
		default:
			break;
		}
	}

	// Output keypresses
	for (int i = 0; i < numkeys; i++)
	{
		if (keyState[i])
		{
			const int test = SDL_GetScancodeFromKey(i);
			SDL_Log("Key Pressed: %i", test);
		}
	}

	sprite2_->spriteInfo.transform.Translate(inputHandler->mouse_dx_, inputHandler->mouse_dy_);

	return false;
}

bool Game::Render(const float dt)
{	
	SDL_Renderer* shRenderer = window_ptr_->GetRenderer();

	SDL_RenderClear(shRenderer);

	SDL_SetRenderDrawColor(shRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	
	time_since_start_ += dt;
	const float translate = 64.0f * std::sinf(time_since_start_);
	transform_.Translate(0.0f, 0.0f);
	transform_.SetSize(translate, 64.0f);
	//transform.Rotate(dt * 60.0);
	const auto localRect = transform_.GetLocationRect();

	Input* input = &Input::GetInstance();
	
	
	SDL_RenderDrawRectF(shRenderer, localRect);

	renderer_.CopyToBuffer(*shRenderer);
	
	SDL_RenderPresent(shRenderer);
	SDL_SetRenderDrawColor(shRenderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	
	return false;
}

void Game::OnWindowEvent(SDL_Event& event)
{
	Input* inputHandler = &Input::GetInstance();
	
	switch (event.type)
	{
	case SDL_WINDOWEVENT_FOCUS_GAINED:
		// TODO: Ignore the movement that will be made on focus gain
		break;
	case SDL_WINDOWEVENT_FOCUS_LOST:
		break;
	default:
		break;
	}
}
