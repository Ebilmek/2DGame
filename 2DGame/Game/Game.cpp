#include "Game.h"

Game::Game() //: WindowPtr(new WindowSDL())
{
	WindowPtr = std::make_unique<WindowSDL>();
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

bool Game::RunGame()
{
	return false;
}
