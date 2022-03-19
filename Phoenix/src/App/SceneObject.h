#pragma once
#include "Events/Event.h"
class ISceneObject
{
public:
	virtual ~ISceneObject() {}
public:
	virtual void update() = 0;
	virtual void onEvent(IEvent& event) = 0 ;
};