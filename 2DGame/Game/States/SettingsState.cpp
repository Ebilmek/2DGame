#include "SettingsState.h"

#include "EventFacade.h"

GameStateEnum SettingsState::Update(const float& _dt)
{
	Input* inputHandler = EventFacade::GetInstance().GetInput();

	if (inputHandler->IsMouseButtonPressed(SDL_BUTTON_RIGHT))
	{
		return GameStateEnum::kMainMenu;
	}
	
	return GameStateEnum::kSettings;
}

void SettingsState::OnEnter()
{
}

void SettingsState::OnExit()
{
}
