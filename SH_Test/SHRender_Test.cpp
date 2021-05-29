/*
 * Renderer/Renderable/TextureHandler
 * Test most of the things!
 * Renderer already includes TextureHandler
 */
#include "gtest/gtest.h"
#include "Renderer.h"
#include "Renderable.h"
#include "WindowSDL.h"

class RendererRenderableTest : public testing::Test
{
public:
	void SetUp() override
	{
		window_->CreateWindow();
		
		SpriteInfo info(std::string(R"(Assets\Images\Ball.jpg)"));
		SpriteInfo info2(std::string(R"(Assets\Images\Gear.png)"));
		
		renderable_ = std::make_shared<Renderable>(info);
		renderable_gear1_ = std::make_shared<Renderable>(info2);
		renderable_gear2_ = std::make_shared<Renderable>(info2);
		
		//renderer_->RegisterRenderable(*renderable_, *renderer);
	}
protected:
	WindowSDL* window_ = new WindowSDL();
	Renderer* renderer_ = new Renderer();
	std::shared_ptr<Renderable> renderable_;
	std::shared_ptr<Renderable> renderable_gear1_;
	std::shared_ptr<Renderable> renderable_gear2_;
};

TEST_F(RendererRenderableTest, SimpleRegisterAndDeregister)
{
	auto* renderer = window_->GetRenderer();
	renderer_->RegisterRenderable(*renderable_, *renderer);

	EXPECT_EQ(1, renderer_->GetStoredTextureAmount());
	EXPECT_EQ(1, renderer_->GetStoredTextureInfoAmount());
	
	renderer_->RemoveRenderable(renderable_);

	EXPECT_EQ(0, renderer_->GetStoredTextureAmount());
	EXPECT_EQ(0, renderer_->GetStoredTextureInfoAmount());
}

TEST_F(RendererRenderableTest, AdvancedRegisterAndDeregister)
{
	auto* renderer = window_->GetRenderer();
	renderer_->RegisterRenderable(*renderable_, *renderer);
	renderer_->RegisterRenderable(*renderable_gear1_, *renderer);
	renderer_->RegisterRenderable(*renderable_gear2_, *renderer);

	EXPECT_EQ(2, renderer_->GetStoredTextureAmount());
	EXPECT_EQ(3, renderer_->GetStoredTextureInfoAmount());

	renderer_->RemoveRenderable(renderable_);
	renderer_->RemoveRenderable(renderable_gear1_);

	EXPECT_EQ(1, renderer_->GetStoredTextureAmount());
	EXPECT_EQ(1, renderer_->GetStoredTextureInfoAmount());

	renderer_->RemoveRenderable(renderable_gear2_);
	// Double delete to see if it can handle it
	renderer_->RemoveRenderable(renderable_gear2_);
	

	EXPECT_EQ(0, renderer_->GetStoredTextureAmount());
	EXPECT_EQ(0, renderer_->GetStoredTextureInfoAmount());
}
