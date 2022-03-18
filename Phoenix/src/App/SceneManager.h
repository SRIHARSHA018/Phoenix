#pragma once 
#include "SceneObject.h"
#include <vector>

class SceneManager
{
public:
	~SceneManager();
public:
	void addSceneObject(ISceneObject* obj);
	void removeSceneObject(ISceneObject* obj);
	void UpdateObjects();
	void onEvent(IEvent& event);
private:
	std::vector<ISceneObject*> x_sceneObjects;
};