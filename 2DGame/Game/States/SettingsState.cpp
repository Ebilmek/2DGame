#include "SettingsState.h"

void SettingsState::OnEnter()
{
}

void SettingsState::OnExit()
{
}

GameStateEnum SettingsState::Update(const float& _dt)
{
	return GameStateEnum::kSettings;
}
