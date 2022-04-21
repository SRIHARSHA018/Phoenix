#include <algorithm>
#include "SceneObjectManager.h"

SceneObjectManager::~SceneObjectManager()
{
	//TODO: save scene before deletion
	if (this->x_scene_objects.size() > 0) {
		//TODO:iterate over every object and call destroy
		this->x_scene_objects.clear();
	}
}

void SceneObjectManager::addSceneObject(ISceneObject* obj)
{
	this->x_scene_objects.emplace_back(obj);
}

void SceneObjectManager::removeSceneObject(ISceneObject* obj)
{
	auto it = std::find(this->x_scene_objects.begin(), this->x_scene_objects.end(), obj);
	if (it != this->x_scene_objects.end())
		this->x_scene_objects.erase(it);

}

void SceneObjectManager::updateObjects()
{
	for (auto it = this->x_scene_objects.begin(); it != this->x_scene_objects.end(); it++) {
		(*it)->update();
	}
}

void SceneObjectManager::onEvent(IEvent& event)
{
	for (auto it = this->x_scene_objects.begin(); it != this->x_scene_objects.end(); it++) {
		(*it)->onEvent(event);
	}
}
