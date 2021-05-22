#pragma once

#include <memory>
#include <utility>

#include "SDL_log.h"
#include "SpriteInfo.h"

/*
 *	Renderable
 *
 *	Base class for images!
 *	Built to be stored with a shared pointer to it
 */

class Renderable: public std::enable_shared_from_this<Renderable>
{
public:
	Renderable() = default;
	virtual ~Renderable() = default;

	// Reduce shared pointer misuse
	std::shared_ptr<Renderable> GetSharedPtr()
	{
		return shared_from_this();
	}
	
	// Overload less than for sorting
	//bool operator<(const Renderable& _rhs) const { return sprite_info.z_value < _rhs.sprite_info.z_value; }
	
	//SpriteInfo sprite_info;
};

//// Weak pointer overload
//inline bool operator==(const std::weak_ptr<const Renderable>& _a, const std::weak_ptr<const Renderable>& _b)
//{
//	// Handle if one or both of the inputs are expired
//	if (_a.expired() || _b.expired())
//	{
//		std::string imageName;
//		// push all of the missing ones to the end
//		if (_a.expired() && _b.expired())
//		{
//			imageName = "unknown, more than one were detected.";
//		}
//		else if (_a.expired())
//		{
//			imageName = _b.lock()->sprite_info.image_name;
//		}
//		else
//		{
//			imageName = _a.lock()->sprite_info.image_name;
//		}
//
//		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderable not found before comparing with: %s", imageName.c_str());
//		return false;
//	}
//	
//	return _a.lock() == _b.lock();
//}
//
//// Weak pointer overload
//inline bool operator<(const std::weak_ptr<const Renderable>& _a, const std::weak_ptr<const Renderable>& _b)
//{
//	// Handle if one or both of the inputs are expired
//	if(_a.expired() || _b.expired())
//	{
//		std::string imageName;
//		bool returnType;
//		// push all of the missing ones to the end
//		if (_a.expired() && _b.expired())
//		{
//			imageName = "unknown, more than one were detected.";
//			returnType = true;
//		}
//		else if(_a.expired())
//		{
//			imageName = _b.lock()->sprite_info.image_name;
//			returnType = false;
//		}
//		else
//		{
//			imageName = _a.lock()->sprite_info.image_name;
//			returnType = true;
//		}
//
//		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderable not found before comparing with: %s", imageName.c_str());
//		return returnType;
//	}
//	
//	return _a.lock()->sprite_info.z_value < _b.lock()->sprite_info.z_value;
//}
