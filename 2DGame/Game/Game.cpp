#include "Game.h"

#include <algorithm>
#include <string>

#include "SDL_rect.h"
#include "EventFacade.h"
#include "RenderableFactory.h"
#include "RendererFacade.h"

Game::Game() : window_ptr_(new WindowSDL()),
               transform_(SDL_FRect(100.f, 100.f, 64.f, 64.f)),
               time_since_start_(0.0f)
{
}

bool Game::StartGame()
{
	window_ptr_->CreateWindow();
	window_ptr_->DisplayWindow();

	const auto& sdlRenderer = window_ptr_->GetRenderer();

	RendererFacade::GetInstance().SetRenderers(&renderer_, sdlRenderer);

	state_handler_->Setup();
	
	const SpriteInfo ballInfo(std::string(R"(Assets\Images\ball.jpg)"));
	const SpriteInfo gearInfo(std::string(R"(Assets\Images\gear.png)"));
	sprite1_ = RenderableFactory::RegisterSprite(ballInfo);
	sprite2_ = RenderableFactory::RegisterSprite(ballInfo);
	sprite3_ = RenderableFactory::RegisterSprite(gearInfo);

	sprite2_->sprite_info.transform.Translate(150.0f, 0.0f);
	sprite3_->sprite_info.transform.Translate(300.0f, 0.0f);

	FontInfo fontInfo(Transform2D(SDL_FRect(0.0f, 0.0f, 0.0f, 0.0f)), "Hello World!", std::string(R"(Assets\Fonts\agane\Agane 55 (roman).ttf)"), 24);
	fontInfo.transform.Translate(100.0f, 500.0f);
	text1_ = RenderableFactory::RegisterFontText(fontInfo);
	fontInfo.text = "Sexy Time!";
	fontInfo.transform.Translate(0.0f, 25.0f);
	text2_ = RenderableFactory::RegisterFontText(fontInfo);
	fontInfo.text = "Testing!";
	fontInfo.transform.Translate(0.0f, 25.0f);
	text3_ = RenderableFactory::RegisterFontText(fontInfo);

	// Initialize input
	const auto [width, height] = window_ptr_->GetWindowSize();
	EventFacade::GetInstance().InitializeInput(width, height);

	/*cursor_ = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	SDL_SetCursor(cursor_);
	auto something = SDL_ShowCursor(SDL_ENABLE);
	if(something < 0)
		SDL_Log("Cursor Error: %s", SDL_GetError());*/

	SpriteInfo cursorInfo(std::string(R"(Assets\Images\Cursors\cursor.png)"));
	cursorInfo.transform.SetSize(17.0f, 24.0f);
	cursorInfo.layer = kAboveEverything;
	cursorInfo.z_value = 1000.0f;
	cursor1_ = RenderableFactory::RegisterSprite(cursorInfo);
	
	SDL_SetRelativeMouseMode(SDL_TRUE);

	image1_ = RenderableFactory::RegisterSprite(ballInfo);
	image1_->sprite_info.transform.SetLocation(600.0f, 600.0f);
	image1_->sprite_info.layer = kMiddleground;
	image1_->sprite_info.z_value = -50.0f;
	image2_ = RenderableFactory::RegisterSprite(ballInfo);
	image2_->sprite_info.transform.SetLocation(650.0f, 600.0f);
	image2_->sprite_info.layer = kMiddleground;
	image3_ = RenderableFactory::RegisterSprite(ballInfo);
	image3_->sprite_info.transform.SetLocation(700.0f, 600.0f);
	image3_->sprite_info.layer = kForeground;
	image4_ = RenderableFactory::RegisterSprite(ballInfo);
	image4_->sprite_info.transform.SetLocation(750.0f, 600.0f);
	image4_->sprite_info.layer = kAboveEverything;
	
	return false;
}

bool Game::StopGame()
{
	RenderableFactory::DeregisterSprite(sprite1_);
	RenderableFactory::DeregisterSprite(sprite2_);
	RenderableFactory::DeregisterSprite(sprite3_);
	
	RenderableFactory::DeregisterFontText(text1_);
	RenderableFactory::DeregisterFontText(text2_);
	RenderableFactory::DeregisterFontText(text3_);

	RenderableFactory::DeregisterSprite(cursor1_);
	
	RenderableFactory::DeregisterSprite(image1_);
	RenderableFactory::DeregisterSprite(image2_);
	RenderableFactory::DeregisterSprite(image3_);
	RenderableFactory::DeregisterSprite(image4_);
	
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
	cursor1_->sprite_info.transform.Translate(mouseMovementX, mouseMovementY);

	// Keep cursor within screen (grab info)
	const auto location = cursor1_->sprite_info.transform.GetLocationRect();
	const std::pair <float, float> windowSize = window_ptr_->GetWindowSize();
	std::pair<float, float> newLocation = std::make_pair(location->x, location->y);

	// Constrain the values
	newLocation.first = std::clamp(newLocation.first, 0.0f, windowSize.first);
	newLocation.second = std::clamp(newLocation.second, 0.0f, windowSize.second);
	cursor1_->sprite_info.transform.SetLocation(newLocation.first, newLocation.second);
	
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
