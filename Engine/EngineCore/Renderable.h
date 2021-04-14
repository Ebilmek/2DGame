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
	explicit Renderable(SpriteInfo info) : spriteInfo(std::move(info)) {}

	// Reduce shared pointer misuse
	std::shared_ptr<Renderable> GetPtr()
	{
		return shared_from_this();
	}
	
	// Overload less than for sorting
	bool operator<(const Renderable& rhs) const { return spriteInfo.zValue < rhs.spriteInfo.zValue; }
	
	SpriteInfo spriteInfo;
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
			imageName = b.lock()->spriteInfo.imageName;
		}
		else
		{
			imageName = a.lock()->spriteInfo.imageName;
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
			imageName = b.lock()->spriteInfo.imageName;
			returnType = false;
		}
		else
		{
			imageName = a.lock()->spriteInfo.imageName;
			returnType = true;
		}

		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderable not found before comparing with: %s", imageName.c_str());
		return returnType;
	}
	
	return a.lock()->spriteInfo.zValue < b.lock()->spriteInfo.zValue;
}
