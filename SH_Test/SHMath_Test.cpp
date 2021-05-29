/*
 * Testing Engine Math... math?
 */
#include "Range.h"
#include "gtest/gtest.h"
#include "Transform2D.h"
//#include "Range.h"

class Transform2DTest : public testing::Test
{
protected:
	Transform2D test_transform_ = Transform2D(SDL_FRect({ 0.0f, 0.0f, 0.0f, 0.0f }));
};

TEST_F(Transform2DTest, GetterRotation)
{
	EXPECT_DOUBLE_EQ(0.0, test_transform_.GetRotation());
}

TEST_F(Transform2DTest, SimpleRotation)
{
	test_transform_.Rotate(50.0);
	EXPECT_DOUBLE_EQ(50.0, test_transform_.GetRotation());
}

TEST_F(Transform2DTest, NormalisationClockwise)
{
	test_transform_.Rotate(380.0);
	EXPECT_DOUBLE_EQ(20.0, test_transform_.GetRotation());
}

TEST_F(Transform2DTest, NormalisationAntiClockwise)
{
	test_transform_.Rotate(-380.0);
	EXPECT_DOUBLE_EQ(340.0, test_transform_.GetRotation());
}

TEST_F(Transform2DTest, NormalisationAntiClockwise2)
{
	test_transform_.Rotate(-720.0);
	EXPECT_DOUBLE_EQ(0.0, test_transform_.GetRotation());
}

TEST_F(Transform2DTest, GetterSize)
{
	EXPECT_FLOAT_EQ(0.0f, test_transform_.GetLocationRect()->w);
	EXPECT_FLOAT_EQ(0.0f, test_transform_.GetLocationRect()->h);
}

TEST_F(Transform2DTest, SizeSet)
{
	test_transform_.SetSize(50.0f, 75.0f);
	EXPECT_FLOAT_EQ(50.0f, test_transform_.GetLocationRect()->w);
	EXPECT_FLOAT_EQ(75.0f, test_transform_.GetLocationRect()->h);
}

TEST_F(Transform2DTest, SizeMultiply)
{
	test_transform_.SetSize(50.0f, 75.0f);
	test_transform_.MultiplySize(2.0f, 2.0f);
	EXPECT_FLOAT_EQ(100.0f, test_transform_.GetLocationRect()->w);
	EXPECT_FLOAT_EQ(150.0f, test_transform_.GetLocationRect()->h);
}

TEST_F(Transform2DTest, SizeMultiplyNegativeBoth)
{
	test_transform_.SetSize(50.0f, 75.0f);
	test_transform_.MultiplySize(-2.0f, -2.0f);
	EXPECT_FLOAT_EQ(50.0f, test_transform_.GetLocationRect()->w);
	EXPECT_FLOAT_EQ(75.0f, test_transform_.GetLocationRect()->h);
}

TEST_F(Transform2DTest, ResizePositiveTest)
{
	test_transform_.SetSize(50.0f, 75.0f);
	test_transform_.SetSize(100.0f, 1500.0f);
	EXPECT_FLOAT_EQ(100.0f, test_transform_.GetLocationRect()->w);
	EXPECT_FLOAT_EQ(1500.0f, test_transform_.GetLocationRect()->h);

	EXPECT_EQ(SDL_FLIP_NONE, test_transform_.GetFlip());
}

TEST_F(Transform2DTest, ResizeNegativeTest)
{
	test_transform_.SetSize(50.0f, 75.0f);
	test_transform_.SetSize(-100.0f, -1500.0f);
	EXPECT_FLOAT_EQ(100.0f, test_transform_.GetLocationRect()->w);
	EXPECT_FLOAT_EQ(1500.0f, test_transform_.GetLocationRect()->h);

	EXPECT_EQ(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL, test_transform_.GetFlip());
}

TEST(RangeTest, RangeTest)
{
	EXPECT_TRUE(SHMath::InRange(0, 10, 5));
	EXPECT_FALSE(SHMath::InRange(0, 10, 11));
}

TEST(RangeTest, NegativeRangeTest)
{
	EXPECT_TRUE(SHMath::InRange(-10, 10, 5));
	EXPECT_TRUE(SHMath::InRange(-10, 10, -10));
	EXPECT_TRUE(SHMath::InRange(-10, -9, -9));
	EXPECT_FALSE(SHMath::InRange(-10, -8, -11));
}
