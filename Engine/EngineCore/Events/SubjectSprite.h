#pragma once
#include <vector>

#include "Event.h"
#include "ObserverSprite.h"
#include "RenderableInfo/SpriteInfo.h"

class SubjectSprite
{
public:
	virtual ~SubjectSprite() { observer_.clear(); }

	void AddObserver(ObserverSprite* _observer);

	void RemoveObserver(ObserverSprite* _observer);

protected:
	void Notify(const SpriteInfo& _info, const Event _event);
	
private:
	std::vector<ObserverSprite*> observer_;
};
