#pragma once

#include <memory>

#include "StateMain.h"

class StateHandler
{
public:
	StateHandler();

	void Update(float _dt);
private:
	void ChangeState();
	
	std::unique_ptr<StateBase> state_ = std::make_unique<MainMenuState>();
	
	GameStateEnum current_state_ = GameStateEnum::kMainMenu;
	GameStateEnum previous_state_ = GameStateEnum::kMainMenu;
};