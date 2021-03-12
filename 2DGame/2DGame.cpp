/*
*	2D Game
*	Stefan Harrison
* 
*	Simple 2D game to learn/brush up on
*	CMake C++ and general techniques
*/
#include <stdio.h>
#include <memory>

#include <SDL.h>

#include "Game/Game.h"

int main(int argc, char* argv[]) 
{
	std::unique_ptr<Game> game(new Game());
	int hasError = 0;
	float dt = 0.0f;

	// Set up
	game->StartGame();

	// Run game loop
	do
	{
		hasError = game->RunGame(dt);
	} while (!hasError);
	
	// Clean up and quit
	game->StopGame();
	SDL_Quit();
	return 0;
}
