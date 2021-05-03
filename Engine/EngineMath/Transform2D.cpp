#include "Transform2D.h"

#include <cmath>

Transform2D::Transform2D(SDL_FRect _pos_and_size, double _rotation, SDL_RendererFlip _flip) :
	pos_and_size_(_pos_and_size),
	rotation_(_rotation),
	flip_(_flip)
{
}

void Transform2D::Translate(float _x, float _y)
{
	pos_and_size_.x += _x;
	pos_and_size_.y += _y;
}

void Transform2D::MultiplySize(float _multiplier_x, float _multiplier_y)
{
	if(_multiplier_x > 0)
	{
		pos_and_size_.w *= _multiplier_x;
	}
	if(_multiplier_y > 0)
	{
		pos_and_size_.h *= _multiplier_y;
	}
}

void Transform2D::SetSize(float _width, float _height)
{
	SDL_RendererFlip mirror = SDL_FLIP_NONE;
	if (_width < 0)
	{
		mirror = SDL_FLIP_HORIZONTAL;
	}
	if (_height < 0)
	{
		// Bitwise or would be fine here too instead
		mirror = static_cast<SDL_RendererFlip>(mirror + SDL_FLIP_VERTICAL);
	}
	
	pos_and_size_.w = std::abs(_width);
	pos_and_size_.h = std::abs(_height);
	flip_ = mirror;
}

void Transform2D::SetSizeNoFlip(float _width, float _height)
{
	if (_width < 0)
		_width *= -1.0f;
	if (_height < 0)
		_height *= -1.0f;
	
	pos_and_size_.w = _width;
	pos_and_size_.h = _height;
}

void Transform2D::Rotate(double _rotation)
{
	rotation_ += _rotation;
	NormaliseRotation();
}

void Transform2D::SetRotation(double _rotation)
{
	rotation_ = _rotation;
	NormaliseRotation();
}

void Transform2D::NormaliseRotation()
{
	rotation_ = std::fmod(rotation_, 360.0);
	if (rotation_ < 0.0)
		rotation_ += 360.0;
}
