#include "Transform2D.h"

#include <cmath>

Transform2D::Transform2D(SDL_FRect in_pos_and_size, double in_rotation, SDL_RendererFlip in_flip) :
	pos_and_size_(in_pos_and_size),
	rotation_(in_rotation),
	flip_(in_flip)
{
}

void Transform2D::Translate(float x, float y)
{
	pos_and_size_.x += x;
	pos_and_size_.y += y;
}

void Transform2D::MultiplySize(float multiplier_x, float multiplier_y)
{
	if(multiplier_x > 0)
	{
		pos_and_size_.w *= multiplier_x;
	}
	if(multiplier_y > 0)
	{
		pos_and_size_.h *= multiplier_y;
	}
}

void Transform2D::SetSize(float width, float height)
{
	SDL_RendererFlip mirror = SDL_FLIP_NONE;
	if (width < 0)
	{
		mirror = SDL_FLIP_HORIZONTAL;
	}
	if (height < 0)
	{
		// Bitwise or would be fine here too instead
		mirror = static_cast<SDL_RendererFlip>(mirror + SDL_FLIP_VERTICAL);
	}
	
	pos_and_size_.w = std::abs(width);
	pos_and_size_.h = std::abs(height);
	flip_ = mirror;
}

void Transform2D::SetSizeNoFlip(float width, float height)
{
	if (width < 0)
		width *= -1.0f;
	if (height < 0)
		height *= -1.0f;
	
	pos_and_size_.w = width;
	pos_and_size_.h = height;
}

void Transform2D::Rotate(double in_rotation)
{
	rotation_ += in_rotation;
	NormaliseRotation();
}

void Transform2D::SetRotation(double in_rotation)
{
	rotation_ = in_rotation;
	NormaliseRotation();
}

void Transform2D::NormaliseRotation()
{
	rotation_ = std::fmod(rotation_, 360.0);
	if (rotation_ < 0.0)
		rotation_ += 360.0;
}
