#include "ReverseSubject.h"

void ReverseSubject::AddObserver(ReverseObserver* _observer)
{
	observer_.push_back(_observer);
}

void ReverseSubject::RemoveObserver(ReverseObserver* _observer)
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

void ReverseSubject::Notify(const InfoBase& _info, const Event _event)
{
	for(ReverseObserver* observer : observer_)
	{
		observer->OnNotify(_info, _event);
	}
}
