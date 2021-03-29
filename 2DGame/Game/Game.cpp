#include "Game.h"

#include <string>

#include "SHDebug.h"
#include "Input.h"

Game::Game() : WindowPtr(new WindowSDL()), position(0.0f)
{
	//WindowPtr = std::make_unique<WindowSDL>();
}

bool Game::StartGame()
{
	WindowPtr->CreateWindow();
	WindowPtr->DisplayWindow();
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

	if(sprite.texture == nullptr)
		sprite.LoadTexture(R"(C:\Users\stefl\OneDrive\Pictures\gear.png)", shRenderer);

	SDL_SetRenderDrawColor(shRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_Rect rect;
	position += dt * 10.0f;
	rect.w = rect.h = 64;
	rect.x = rect.y = 100 + position;
	SDL_RenderDrawRect(shRenderer, &rect);

	if(sprite.texture != nullptr)
		SDL_RenderCopy(shRenderer, sprite.texture, nullptr, &rect);
	
	SDL_RenderPresent(shRenderer);
	SDL_SetRenderDrawColor(shRenderer, 0x00, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	
	return false;
}
