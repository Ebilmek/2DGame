#include "Transform2D.h"

#include <cmath>

Transform2D::Transform2D(SDL_FRect inPosAndSize, double inRotation, SDL_RendererFlip inFlip) :
	posAndSize(inPosAndSize),
	rotation(inRotation),
	flip(inFlip)
{
}

void Transform2D::Translate(float x, float y)
{
	posAndSize.x += x;
	posAndSize.y += y;
}

void Transform2D::MultiplySize(float multiplierX, float multiplierY)
{
	if(multiplierX > 0)
	{
		posAndSize.w *= multiplierX;
	}
	if(multiplierY > 0)
	{
		posAndSize.h *= multiplierY;
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
	
	posAndSize.w = std::abs(width);
	posAndSize.h = std::abs(height);
	flip = mirror;
}

void Transform2D::SetSizeNoFlip(float width, float height)
{
	if (width < 0)
		width *= -1.0f;
	if (height < 0)
		height *= -1.0f;
	
	posAndSize.w = width;
	posAndSize.h = height;
}

void Transform2D::Rotate(double inRotation)
{
	rotation += inRotation;
	NormaliseRotation();
}

void Transform2D::SetRotation(double inRotation)
{
	rotation = inRotation;
	NormaliseRotation();
}

void Transform2D::NormaliseRotation()
{
	rotation = std::fmod(rotation, 360.0);
	if (rotation < 0.0)
		rotation += 360.0;
}
