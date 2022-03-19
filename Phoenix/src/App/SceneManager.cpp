#include "SceneManager.h"
#include <algorithm>

SceneManager::~SceneManager()
{
	//TODO: save scene before deletion
	if (this->x_sceneObjects.size() > 0) {
		//TODO:iterate over every object and call destroy
		this->x_sceneObjects.clear();
	}
}

void SceneManager::addSceneObject(ISceneObject* obj)
{
	this->x_sceneObjects.emplace_back(obj);
}

void SceneManager::removeSceneObject(ISceneObject* obj)
{
	auto it = std::find(this->x_sceneObjects.begin(), this->x_sceneObjects.end(), obj);
	if (it != this->x_sceneObjects.end())
		this->x_sceneObjects.erase(it);

}

void SceneManager::updateObjects()
{
	for (auto it = this->x_sceneObjects.begin(); it != this->x_sceneObjects.end(); it++) {
		(*it)->update();
	}
}

void SceneManager::onEvent(IEvent& event)
{
	for (auto it = this->x_sceneObjects.begin(); it != this->x_sceneObjects.end(); it++) {
		(*it)->onEvent(event);
	}
}
