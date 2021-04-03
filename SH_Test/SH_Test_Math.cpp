/*
 * Testing Engine Math... math?
 */
#include "gtest/gtest.h"
#include "Transform2D.h"

class TransformRotationTest : public testing::Test
{
protected:
	Transform2D testTransform = Transform2D(SDL_FRect({ 0.0f, 0.0f, 0.0f, 0.0f }));
};

TEST_F(TransformRotationTest, GetterRotation)
{
	EXPECT_DOUBLE_EQ(0.0, testTransform.GetRotation());
}

TEST_F(TransformRotationTest, SimpleRotation)
{
	testTransform.Rotate(50.0);
	EXPECT_DOUBLE_EQ(50.0, testTransform.GetRotation());
}

TEST_F(TransformRotationTest, NormalisationClockwise)
{
	testTransform.Rotate(380.0);
	EXPECT_DOUBLE_EQ(20.0, testTransform.GetRotation());
}

TEST_F(TransformRotationTest, NormalisationAntiClockwise)
{
	testTransform.Rotate(-380.0);
	EXPECT_DOUBLE_EQ(340.0, testTransform.GetRotation());
}

TEST_F(TransformRotationTest, NormalisationAntiClockwise2)
{
	testTransform.Rotate(-720.0);
	EXPECT_DOUBLE_EQ(0.0, testTransform.GetRotation());
}

TEST_F(TransformRotationTest, GetterSize)
{
	EXPECT_FLOAT_EQ(0.0f, testTransform.GetLocationRect().w);
	EXPECT_FLOAT_EQ(0.0f, testTransform.GetLocationRect().h);
}

TEST_F(TransformRotationTest, SizeSet)
{
	testTransform.SetSize(50.0f, 75.0f);
	EXPECT_FLOAT_EQ(50.0f, testTransform.GetLocationRect().w);
	EXPECT_FLOAT_EQ(75.0f, testTransform.GetLocationRect().h);
}

TEST_F(TransformRotationTest, SizeMultiply)
{
	testTransform.SetSize(50.0f, 75.0f);
	testTransform.MultiplySize(2.0f, 2.0f);
	EXPECT_FLOAT_EQ(100.0f, testTransform.GetLocationRect().w);
	EXPECT_FLOAT_EQ(150.0f, testTransform.GetLocationRect().h);
}

TEST_F(TransformRotationTest, SizeMultiplyNegativeHorizontal)
{
	testTransform.SetSize(50.0f, 75.0f);
	testTransform.MultiplySize(-2.0f, 2.0f);
	EXPECT_FLOAT_EQ(-100.0f, testTransform.GetLocationRect().w);
	EXPECT_FLOAT_EQ(150.0f, testTransform.GetLocationRect().h);

	EXPECT_EQ(SDL_FLIP_HORIZONTAL, testTransform.GetFlip());
}

TEST_F(TransformRotationTest, SizeMultiplyNegativeBoth)
{
	testTransform.SetSize(50.0f, 75.0f);
	testTransform.MultiplySize(-2.0f, -2.0f);
	EXPECT_FLOAT_EQ(-100.0f, testTransform.GetLocationRect().w);
	EXPECT_FLOAT_EQ(-150.0f, testTransform.GetLocationRect().h);

	EXPECT_EQ((SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL), testTransform.GetFlip());
}