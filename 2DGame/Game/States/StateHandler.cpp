#include "StateHandler.h"

StateHandler::StateHandler()
{
	state_->OnEnter();
}

void StateHandler::Update(const float _dt)
{
	current_state_ = state_->Update(_dt);

	if(current_state_ != previous_state_)
	{
		state_->OnExit();
		state_.reset();
		ChangeState();
		state_->OnEnter();
		previous_state_ = current_state_;
	}
}

void StateHandler::ChangeState()
{
	switch (current_state_)
	{
	case GameStateEnum::kMainMenu:
		state_ = std::make_unique<MainMenuState>();
		break;
	case GameStateEnum::kSettings:
		state_ = std::make_unique<SettingsState>();
		break;
	case GameStateEnum::kGame:
		state_ = std::make_unique<GameState>();
		break;
	default: 
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Expecting to create a GameState that is not implemented");
		SDL_Log("GameState implementation missing");
	}
}
