#include "GUIManager.h"

GUIManager::~GUIManager()
{
	if (this->x_uiComponents.size() > 0)
	this->x_uiComponents.clear();
}

void GUIManager::addUIComponent(IUIComponent* obj)
{
	this->x_uiComponents.emplace_back(obj);
}

void GUIManager::removeUIComponent(IUIComponent* obj)
{
	auto it = std::find(this->x_uiComponents.begin(), this->x_uiComponents.end(), obj);
	if (it != this->x_uiComponents.end())
		this->x_uiComponents.erase(it);
}

void GUIManager::UpdateUIComponents()
{
	for (auto it = this->x_uiComponents.begin(); it != this->x_uiComponents.end(); it++) {
		(*it)->update();
	}

}

void GUIManager::onEvent(IEvent& event)
{
	for (auto it = this->x_uiComponents.begin(); it != this->x_uiComponents.end(); it++) {
		(*it)->onEvent(event);
	}
}

