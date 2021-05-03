#include "GameState.h"

void GameState::OnEnter()
{
}

void GameState::OnExit()
{
}

GameStateEnum GameState::Update(const float& _dt)
{
	return GameStateEnum::kGame;
}
