#pragma once

#include <memory>
#include <utility>

#include "SDL_log.h"
#include "SpriteInfo.h"

/*
 * Built to be stored with a shared pointer to it
 * Register with a 
 */

class Renderable: public std::enable_shared_from_this<Renderable>
{
public:
	explicit Renderable(SpriteInfo info) : sprite_info(std::move(info)) {}

	// Reduce shared pointer misuse
	std::shared_ptr<Renderable> GetSharedPtr()
	{
		return shared_from_this();
	}
	
	// Overload less than for sorting
	bool operator<(const Renderable& rhs) const { return sprite_info.zValue < rhs.sprite_info.zValue; }
	
	SpriteInfo sprite_info;
};

// Weak pointer overload
inline bool operator==(const std::weak_ptr<const Renderable>& a, const std::weak_ptr<const Renderable>& b)
{
	// Handle if one or both of the inputs are expired
	if (a.expired() || b.expired())
	{
		std::string imageName;
		// push all of the missing ones to the end
		if (a.expired() && b.expired())
		{
			imageName = "unknown, more than one were detected.";
		}
		else if (a.expired())
		{
			imageName = b.lock()->sprite_info.imageName;
		}
		else
		{
			imageName = a.lock()->sprite_info.imageName;
		}

		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderable not found before comparing with: %s", imageName.c_str());
		return false;
	}
	
	return a.lock() == b.lock();
}

// Weak pointer overload
inline bool operator<(const std::weak_ptr<const Renderable>& a, const std::weak_ptr<const Renderable>& b)
{
	// Handle if one or both of the inputs are expired
	if(a.expired() || b.expired())
	{
		std::string imageName;
		bool returnType;
		// push all of the missing ones to the end
		if (a.expired() && b.expired())
		{
			imageName = "unknown, more than one were detected.";
			returnType = true;
		}
		else if(a.expired())
		{
			imageName = b.lock()->sprite_info.imageName;
			returnType = false;
		}
		else
		{
			imageName = a.lock()->sprite_info.imageName;
			returnType = true;
		}

		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderable not found before comparing with: %s", imageName.c_str());
		return returnType;
	}
	
	return a.lock()->sprite_info.zValue < b.lock()->sprite_info.zValue;
}
