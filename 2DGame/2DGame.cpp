/*
*	2D Game
*	Stefan Harrison
* 
*	Simple 2D game to learn/brush up on
*	CMake C++ and general techniques
*/
#include <stdio.h>
#include <memory>
#include <chrono>

#include <SDL.h>

#include "Game/Game.h"

int main(int argc, char* argv[]) 
{
	std::unique_ptr<Game> game = std::make_unique<Game>();
	int isExiting = 0;
	float dt = 0;

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS);

	// Set up
	game->StartGame();

	// Run game loop
	do
	{
		// Uint32 preFrameTime = SDL_GetTicks();
		std::chrono::steady_clock::time_point chronoPreTime = std::chrono::high_resolution_clock::now();
		// TODO: Frame rate
		// Game Loop
		isExiting = game->RunGame(dt);
		if(!isExiting)
		{
			game->Render(dt);
		}

		// Timing
		// Calculate dt, in seconds (6 sig fig)
		// dt = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::milliseconds(SDL_GetTicks() - preFrameTime)).count();
		dt = std::chrono::duration<float, std::chrono::seconds::period>(std::chrono::high_resolution_clock::now() - chronoPreTime).count();
	} while (!isExiting);
	
	// Clean up and quit
	game->StopGame();
	SDL_Quit();
	return 0;
}
