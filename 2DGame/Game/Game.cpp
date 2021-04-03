#include "Game.h"

#include <string>
#include <cmath>

#include "SDL_rect.h"
#include "SHDebug.h"
#include "Input.h"

Game::Game() : WindowPtr(new WindowSDL()),
	transform(SDL_FRect({ 100.f, 100.f, 64.f, 64.f })),
	sprite1(std::make_shared<Renderable>(std::string(R"(C:\Users\stefl\OneDrive\Pictures\ball.jpg)"))),
	sprite2(std::make_shared<Renderable>(std::string(R"(C:\Users\stefl\OneDrive\Pictures\ball.jpg)"))),
	sprite3(std::make_shared<Renderable>(std::string(R"(C:\Users\stefl\OneDrive\Pictures\ball.jpg)"))),
	timeSinceStart(0.0f)
{
	//WindowPtr = std::make_unique<WindowSDL>();
	sprite2->spriteInfo.transform.Translate(100.0f, 0.0f);
	sprite3->spriteInfo.transform.Translate(200.0f, 0.0f);
}

bool Game::StartGame()
{
	WindowPtr->CreateWindow();
	WindowPtr->DisplayWindow();

	SDL_Renderer* shRenderer = WindowPtr->GetRenderer();
	renderer.RegisterRenderable(sprite1, shRenderer);
	renderer.RegisterRenderable(sprite2, shRenderer);
	renderer.RegisterRenderable(sprite3, shRenderer);
	
	return false;
}

bool Game::StopGame()
{
	if (WindowPtr)
	{
		WindowPtr->DeleteWindow();
		WindowPtr = nullptr;
	}
	return false;
}

bool Game::RunGame(float dt)
{
	SDL_Event event;
	Input* inputHandler = nullptr;
	inputHandler->getInstance();

	// Event loop
	while(SDL_PollEvent(&event))
	{
		if (event.type > SDL_KEYDOWN && event.type < SDL_MULTIGESTURE)
		{
			inputHandler->HandleEvents(event);
			continue;
		}

		switch(event.type)
		{
		case SDL_QUIT:
			StopGame();
			return true;
		
		default:
			break;
		}
	}
	
	// Exit clause
	// @TODO: replace with input variant	
	int numkeys;
	const Uint8* keyState = SDL_GetKeyboardState(&numkeys);
	
	for (int i = 0; i < numkeys; i++)
	{
		if (keyState[i])
		{
			const int test = SDL_GetScancodeFromKey(i);
			SDL_Log("Key Pressed: %i", test);
		}
	}
	
	
	if (keyState[SDL_SCANCODE_ESCAPE])
		return true;

	return false;
}

bool Game::Render(float dt)
{	
	SDL_Renderer* shRenderer = WindowPtr->GetRenderer();

	SDL_RenderClear(shRenderer);

	SDL_SetRenderDrawColor(shRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	
	timeSinceStart += dt;
	const float translate = 64.0f * std::sinf(timeSinceStart);
	transform.Translate(0.0f, 0.0f);
	transform.SetSize(translate, 64.0f);
	//transform.Rotate(dt * 60.0);
	auto localRect = transform.GetLocationRect();
	
	SDL_RenderDrawRectF(shRenderer, &localRect);

	renderer.CopyToBuffer(shRenderer);
	
	SDL_RenderPresent(shRenderer);
	SDL_SetRenderDrawColor(shRenderer, 0x00, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	
	return false;
}
