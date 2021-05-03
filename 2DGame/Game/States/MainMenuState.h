#pragma once
#include "Sprite.h"
#include "StateBase.h"

class MainMenuState final : public StateBase
{
public:
	MainMenuState();
	
	void OnEnter() override;
	void OnExit() override;
	GameStateEnum Update(const float& _dt) override;

private:
	Sprite* background_;
};
