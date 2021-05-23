#include "Game.h"

#include <string>

#include "SDL_rect.h"
#include "EventFacade.h"
#include "RenderableFactory.h"

Game::Game() : window_ptr_(new WindowSDL()),
               transform_(SDL_FRect(100.f, 100.f, 64.f, 64.f)),
               time_since_start_(0.0f)
{
	//windowPtr = std::make_unique<WindowSDL>();
}

bool Game::StartGame()
{
	window_ptr_->CreateWindow();
	window_ptr_->DisplayWindow();

	const auto& shRenderer = window_ptr_->GetRenderer();
	const SpriteInfo ballInfo(std::string(R"(Assets\Images\ball.jpg)"));
	const SpriteInfo gearInfo(std::string(R"(Assets\Images\gear.png)"));
	sprite1_ = RenderableFactory::RegisterSprite(ballInfo, *shRenderer, renderer_);
	sprite2_ = RenderableFactory::RegisterSprite(ballInfo, *shRenderer, renderer_);
	sprite3_ = RenderableFactory::RegisterSprite(gearInfo, *shRenderer, renderer_);

	sprite2_->sprite_info.transform.Translate(150.0f, 0.0f);
	sprite3_->sprite_info.transform.Translate(300.0f, 0.0f);

	FontInfo fontInfo(Transform2D(SDL_FRect(0.0f, 0.0f, 0.0f, 0.0f)), "Hello World!", std::string(R"(Assets\Fonts\agane\Agane 55 (roman).ttf)"), 24);
	fontInfo.transform.Translate(100.0f, 500.0f);
	text1_ = RenderableFactory::RegisterFontText(fontInfo, *shRenderer, renderer_);
	fontInfo.text = "Sexy Time!";
	fontInfo.transform.Translate(0.0f, 25.0f);
	text2_ = RenderableFactory::RegisterFontText(fontInfo, *shRenderer, renderer_);
	fontInfo.text = "Testing!";
	fontInfo.transform.Translate(0.0f, 25.0f);
	text3_ = RenderableFactory::RegisterFontText(fontInfo, *shRenderer, renderer_);

	// Initialize input
	const auto [width, height] = window_ptr_->GetWindowSize();
	EventFacade::GetInstance().InitializeInput(width, height);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	return false;
}

bool Game::StopGame()
{
	RenderableFactory::DeregisterSprite(sprite1_, renderer_);
	RenderableFactory::DeregisterSprite(sprite2_, renderer_);
	RenderableFactory::DeregisterSprite(sprite3_, renderer_);
	
	RenderableFactory::DeregisterFontText(text1_, renderer_);
	RenderableFactory::DeregisterFontText(text2_, renderer_);
	RenderableFactory::DeregisterFontText(text3_, renderer_);
	
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

	//// Output keypresses
	//inputHandler->OutputAllPressedKeys();

	//if(inputHandler->IsMouseButtonPressed(SDL_BUTTON_LEFT))
	//{
	//	sprite1_->sprite_info.transform.Translate(0.0f, 100.f);
	//}
	//if (inputHandler->IsMouseButtonPressed(SDL_BUTTON_RIGHT))
	//{
	//	sprite1_->sprite_info.transform.Translate(0.0f, -100.f);
	//}

	state_handler_->Update(_dt);

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

	renderer_.CopyToBuffer(shRenderer);
	
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
