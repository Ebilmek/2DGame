#include "SubjectSprite.h"

void SubjectSprite::AddObserver(ObserverSprite* _observer)
{
	observer_.push_back(_observer);
}

void SubjectSprite::RemoveObserver(ObserverSprite* _observer)
{
	for(auto it = observer_.begin(); 
	    it != observer_.end(); ++it)
	{
		if(*it == _observer)
		{
			observer_.erase(it);
		}
	}
}

void SubjectSprite::Notify(const SpriteInfo& _info, const Event _event)
{
	for(ObserverSprite* observer : observer_)
	{
		observer->OnNotify(_info, _event);
	}
}
