#pragma once 
#include "SceneObject.h"
#include <vector>

class SceneObjectManager
{
public:
	~SceneObjectManager();

public:
	void addSceneObject(ISceneObject* obj);
	void removeSceneObject(ISceneObject* obj);
	void updateObjects();
	void onEvent(IEvent& event);

private:
	std::vector<ISceneObject*> x_sceneObjects;
};