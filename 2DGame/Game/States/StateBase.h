#pragma once
#include "StateList.h"

class StateBase
{
public:
	virtual ~StateBase() = default;

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual GameStateEnum Update(const float& dt) = 0;
};
