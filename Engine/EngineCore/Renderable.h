#pragma once

#include <memory>
#include <utility>

#include "SDL_log.h"
#include "RenderableInfo/SpriteInfo.h"

/*
 * Built to be stored with a shared pointer to it
 * Register with a 
 */

class Renderable: public std::enable_shared_from_this<Renderable>
{
public:
	explicit Renderable(SpriteInfo _info) : sprite_info(std::move(_info)) {}

	// Reduce shared pointer misuse
	std::shared_ptr<Renderable> GetSharedPtr()
	{
		return shared_from_this();
	}
	
	// Overload less than for sorting
	bool operator<(const Renderable& _rhs) const { return sprite_info.z_value < _rhs.sprite_info.z_value; }
	
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
			imageName = b.lock()->sprite_info.image_name;
		}
		else
		{
			imageName = a.lock()->sprite_info.image_name;
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
			imageName = b.lock()->sprite_info.image_name;
			returnType = false;
		}
		else
		{
			imageName = a.lock()->sprite_info.image_name;
			returnType = true;
		}

		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderable not found before comparing with: %s", imageName.c_str());
		return returnType;
	}
	
	return a.lock()->sprite_info.z_value < b.lock()->sprite_info.z_value;
}
