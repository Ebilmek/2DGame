#pragma once
#include "Sprite.h"
#include "StateBase.h"
#include "TextRenderable.h"

class MainMenuState final : public StateBase
{
public:
	GameStateEnum Update(const float& _dt) override;

	void OnEnter() override;
	void OnExit() override;
private:
	std::shared_ptr<Sprite> background_;
	std::shared_ptr<TextRenderable> title_;
};
