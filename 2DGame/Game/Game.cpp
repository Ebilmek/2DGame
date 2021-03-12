#include "Game.h"

#include <string>

#include "SHDebug.h"

Game::Game() : WindowPtr(new WindowSDL())
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
	WindowPtr->DeleteWindow();
	WindowPtr = nullptr;
	return false;
}

bool Game::RunGame(float dt)
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
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
