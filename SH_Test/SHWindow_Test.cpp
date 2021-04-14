/*
 * Test Window Wrapper
 */
#include "gtest/gtest.h"
#include "WindowSDL.h"

TEST(ApplicationWindow, Creation)
{
	auto* window = new WindowSDL();
	const bool hasFaults = window->CreateWindow();

	EXPECT_NE(nullptr, window);
	EXPECT_EQ(sizeof(WindowSDL), sizeof(*window));
	EXPECT_EQ(false, hasFaults);

	window->DeleteWindow();
}

TEST(ApplicationWindow, Deletion)
{
	auto* window = new WindowSDL();
	window->CreateWindow();
	const bool hasFaults = window->DeleteWindow();

	EXPECT_EQ(false, window->IsValid());
	EXPECT_EQ(false, hasFaults);
}

TEST(ApplicationWindow, Recreation)
{
	auto* window = new WindowSDL();
	window->CreateWindow(100, 200, "TestWindow");
	window->RegenerateWindow(300, 400, "TestWindow2");

	const std::pair<uint16_t, uint16_t> output = window->GetWindowSize();

	EXPECT_EQ(output.first, 300);
	EXPECT_EQ(output.second, 400);
	EXPECT_NE(nullptr, window);
}