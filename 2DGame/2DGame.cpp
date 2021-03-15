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
	int isExiting = 0;
	float dt = 0;
	Uint32 pre_frame_time = 0;
	Uint32 post_frame_time = 0;

	// Set up
	game->StartGame();

	// Run game loop
	do
	{
		pre_frame_time = SDL_GetTicks();
		isExiting = game->RunGame(dt);
		post_frame_time = SDL_GetTicks();
		// Calculate dt and convert to seconds
		dt =  (post_frame_time - pre_frame_time) / 1000.f;
	} while (!isExiting);
	
	// Clean up and quit
	SDL_Quit();
	return 0;
}
