#include "MainMenuState.h"
#include "RenderableFactory.h"

GameStateEnum MainMenuState::Update(const float& _dt)
{
	return GameStateEnum::kMainMenu;
}

void MainMenuState::OnEnter()
{
	SpriteInfo backgroundInfo(std::string(R"(Assets\Images\MainMenu\MenuSplash.png)"), Transform2D(SDL_FRect({ 0.0f, 0.0f, 1920.0f, 1080.0f })), kBackground);
	background_ = RenderableFactory::RegisterSprite(backgroundInfo);

	FontInfo fontInfo(Transform2D(SDL_FRect(700.0f, 50.0f, 0.0f, 0.0f)), "2D Game - Tower Defence", std::string(R"(Assets\Fonts\agane\Agane 55 (roman).ttf)"), 32);
	title_ = RenderableFactory::RegisterFontText(fontInfo);
}

void MainMenuState::OnExit()
{
	RenderableFactory::DeregisterSprite(background_);
	RenderableFactory::DeregisterFontText(title_);
}
