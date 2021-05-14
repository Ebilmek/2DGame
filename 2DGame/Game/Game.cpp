#include "Game.h"

#include <string>

#include "SDL_rect.h"
#include "EventFacade.h"

Game::Game() : window_ptr_(new WindowSDL()),
               transform_(SDL_FRect({100.f, 100.f, 64.f, 64.f})),
               sprite1_(std::make_shared<Sprite>(std::string(R"(Assets\Images\ball.jpg)"))),
               sprite2_(std::make_shared<Sprite>(std::string(R"(Assets\Images\ball.jpg)"))),
               sprite3_(std::make_shared<Sprite>(std::string(R"(Assets\Images\gear.png)"))),
               time_since_start_(0.0f),
               font_(new Font(std::string(R"(Assets\Fonts\agane\Agane 55 (roman).ttf)"))),
               text_(std::make_shared<TextRenderable>(SpriteInfo("")))
{
	//windowPtr = std::make_unique<WindowSDL>();
	sprite2_->sprite_info.transform.Translate(150.0f, 0.0f);
	sprite3_->sprite_info.transform.Translate(300.0f, 0.0f);
}

bool Game::StartGame()
{
	window_ptr_->CreateWindow();
	window_ptr_->DisplayWindow();

	const auto shRenderer = window_ptr_->GetRenderer();
	renderer_.RegisterRenderable(*sprite1_, *shRenderer);
	renderer_.RegisterRenderable(*sprite2_, *shRenderer);
	renderer_.RegisterRenderable(*sprite3_, *shRenderer);

	text_->sprite_info.transform.Translate(100.0f, 500.0f);
	text_->sprite_info.z_value = 100.0f;
	renderer_.RegisterRenderable(*text_, *shRenderer, "Hi there!", font_);

	// Initialize input
	const auto [width, height] = window_ptr_->GetWindowSize();
	EventFacade::GetInstance().InitializeInput(width, height);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	return false;
}

bool Game::StopGame()
{
	renderer_.RemoveRenderable(sprite1_);
	renderer_.RemoveRenderable(sprite2_);
	renderer_.RemoveRenderable(sprite3_);
	renderer_.RemoveRenderable(text_);
	
	return false;
}

bool Game::RunGame(const float& _dt)
{
	SDL_Event event;
	Input* inputHandler = EventFacade::GetInstance().GetInput();

	inputHandler->PreUpdate();

	// Exit clause
	if (inputHandler->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		SDL_Event quit;
		quit.type = SDL_QUIT;
		SDL_PushEvent(&quit);
	}
	
	// Event loop
	// TODO: Could multi-thread this, each event type could have its own thread
	// TODO: Limit the time of this (limit how many events are read each frame?), just in case of a large influx of events stalling the game
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
			return true;
		default:
			break;
		}
	}

	// Output keypresses
	inputHandler->OutputAllPressedKeys();

	if(inputHandler->IsMouseButtonPressed(SDL_BUTTON_LEFT))
	{
		sprite1_->sprite_info.transform.Translate(0.0f, 100.f);
	}
	if (inputHandler->IsMouseButtonPressed(SDL_BUTTON_RIGHT))
	{
		sprite1_->sprite_info.transform.Translate(0.0f, -100.f);
	}

	//const auto mouseMovement = inputHandler->GetMouseDelta();
	const auto [mouseMovementX, mouseMovementY] = inputHandler->GetMouseDelta();
	sprite2_->sprite_info.transform.Translate(mouseMovementX, mouseMovementY);
	inputHandler = nullptr;

	time_since_start_ += _dt;
	const float translate = 64.0f * std::sinf(time_since_start_);
	transform_.Translate(0.0f, 0.0f);
	transform_.SetSize(translate, 64.0f);

	return false;
}

bool Game::Render(const float& _dt)
{	
	SDL_Renderer* shRenderer = window_ptr_->GetRenderer();

	SDL_RenderClear(shRenderer);

	renderer_.CopyToBuffer(*shRenderer);
	
	SDL_RenderPresent(shRenderer);
	SDL_SetRenderDrawColor(shRenderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	
	return false;
}

void Game::OnWindowEvent(SDL_Event& _event)
{
	Input* inputHandler = EventFacade::GetInstance().GetInput();
	
	switch (_event.type)
	{
	case SDL_WINDOWEVENT_FOCUS_GAINED:
		// TODO: Ignore the movement that will be made on focus gain
		break;
	case SDL_WINDOWEVENT_FOCUS_LOST:
		// TODO: Pause the game? Stop input going nuts?
		break;
	default:
		break;
	}
}
