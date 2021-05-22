#pragma once
#include <vector>

#include "Event.h"
#include "ObserverFont.h"
#include "RenderableInfo/FontInfo.h"

class SubjectFont
{
public:
	virtual ~SubjectFont() { observer_.clear(); }

	void AddObserver(ObserverFont* _observer);

	void RemoveObserver(ObserverFont* _observer);

protected:
	void Notify(const FontInfo& _info, const Event _event);
	
private:
	std::vector<ObserverFont*> observer_;
};
