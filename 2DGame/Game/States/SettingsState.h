#pragma once
#include "StateBase.h"

class SettingsState final : public StateBase
{
public:
	void OnEnter() override;
	void OnExit() override;
	GameStateEnum Update(const float& _dt) override;
};
