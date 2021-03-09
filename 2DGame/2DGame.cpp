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

	/*do
	{
		hasError = game->StartGame();
	} while (!hasError);*/

	game->StartGame();
	SDL_Delay(2000);
	game->StopGame();
	
	SDL_Quit();
	return 0;
}
