#pragma once
#include "StateBase.h"

class GameState final : public StateBase
{
public:
	void OnEnter() override;
	void OnExit() override;
	GameStateEnum Update(const float& dt) override;
};
