#include "SubjectFont.h"

void SubjectFont::AddObserver(ObserverFont* _observer)
{
	observer_.push_back(_observer);
}

void SubjectFont::RemoveObserver(ObserverFont* _observer)
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

void SubjectFont::Notify(const FontInfo& _info, const Event _event)
{
	for(ObserverFont* observer : observer_)
	{
		observer->OnNotify(_info, _event);
	}
}
