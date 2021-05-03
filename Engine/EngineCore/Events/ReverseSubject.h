#pragma once
#include <vector>

#include "Event.h"
#include "ReverseObserver.h"
#include "RenderableInfo/InfoBase.h"

class ReverseSubject
{
public:
	virtual ~ReverseSubject() { observer_.clear(); }

	void AddObserver(ReverseObserver* _observer);

	void RemoveObserver(ReverseObserver* _observer);

protected:
	void Notify(const InfoBase& _info, const Event _event);
	
private:
	std::vector<ReverseObserver*> observer_;
};
