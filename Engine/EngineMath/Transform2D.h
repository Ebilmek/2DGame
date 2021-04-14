#pragma once
#include "SDL_rect.h"
#include "SDL_render.h"

/*
 * Transform 2D
 * 
 * This will be an overly simple transform type for sprite locations
 * rotations and sizes. Normal transforms would be a transform matrix to apply
 * a position etc. but for what this engine will be used for is overly complex.
 */

class Transform2D
{
public:
	/**
	 *	\param in_pos_and_size SDL_FRect containing position and size
	 *	\param in_rotation Starting rotation in degrees 
	 *	\param in_flip Current mirrored direction, can use bitwise OR to flip in two directions
	 */
	Transform2D(SDL_FRect in_pos_and_size, double in_rotation = 0.0, SDL_RendererFlip in_flip = SDL_FLIP_NONE);

	/**
	 *	\brief Move position by x and y amount
	 *
	 *	\param x Amount to move horizontally
	 *	\param y Amount to move vertically
	 */
	void Translate(float x, float y);

	/**
	 *	\brief Getter for position and size SDL_FRect
	 *
	 *	\return position and size SDL_FRect
	 */
	const SDL_FRect* GetLocationRect() const { return &pos_and_size_; }

	/**
	 *	\brief Increase or decrease size with a multiplier
	 *
	 *	\param multiplier_x Amount to multiply width with, set to -1 to ignore (<0)
	 *	\param multiplier_y Amount to multiply height with, set to -1 to ignore (<0)
	 */
	void MultiplySize(float multiplier_x, float multiplier_y);

	/**
	 *	\brief Sets the size of the rect, will flip automatically
	 *
	 *	\param width Amount to set width to, negative will flip it in this direction
	 *	\param height Amount to multiply height with, set to -1 to ignore (<0)
	 */
	void SetSize(float width, float height);
	
	/**
	 *	\brief Sets the size of the rect, will not flip if size is negative
	 *
	 *	\param width Amount to set width to, negative will flip it in this direction
	 *	\param height Amount to multiply height with, set to -1 to ignore (<0)
	 */
	void SetSizeNoFlip(float width, float height);

	/**
	 *	\brief Rotate by set amount of degrees
	 *
	 *	\param in_rotation in degrees
	 */
	void Rotate(double in_rotation);

	/**
		 *	\brief Rotate by set amount of degrees
		 *
		 *	\param in_rotation in degrees
		 */
	void SetRotation(double in_rotation);

	/**
	 *	\brief Getter for rotation 
	 *
	 *	\return double rotation
	 */
	double GetRotation() const { return rotation_; }

	/**
	 *	\brief Getter for flip
	 *
	 *	\return SDL_RendererFlip which axes it's mirrored on
	 */
	SDL_RendererFlip GetFlip() const { return flip_; }
private:
	/**
	 *	\brief Ensures rotation is within 360 degrees
	 *	\warning May give bad results when inputs are close but not exact to integers
	 */
	void NormaliseRotation();
private:
	/**
	 *	\brief Uses SDL_FRect
	 */
	SDL_FRect pos_and_size_;
	
	/**
	 *	\brief Current rotation, normalised to 0-360, degrees are used, rotation is clockwise
	 */
	double rotation_;
	
	/**
	 *	\brief Uses SDL_RendererFlip
	 */
	SDL_RendererFlip flip_;
};