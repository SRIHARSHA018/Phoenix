#pragma once 
#include <vector>

#include "SceneObject.h"

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
	std::vector<ISceneObject*> x_scene_objects;
};