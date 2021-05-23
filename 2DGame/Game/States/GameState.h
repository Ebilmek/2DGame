#pragma once
#include "StateBase.h"

class GameState final : public StateBase
{
public:
	GameStateEnum Update(const float& _dt) override;
	void OnEnter() override;
	void OnExit() override;
};
