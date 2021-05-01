#pragma once
#include "StateBase.h"

class SettingsState final : public StateBase
{
public:
	SettingsState();
	
	void OnEnter() override;
	void OnExit() override;
	GameStateEnum Update(const float& dt) override;
};
