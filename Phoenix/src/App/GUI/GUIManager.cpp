#include "GUIManager.h"

GUIManager::~GUIManager()
{
	if (this->x_ui_components.size() > 0)
		this->x_ui_components.clear();
}

void GUIManager::addUIComponent(IUIComponent* obj)
{
	this->x_ui_components.emplace_back(obj);
}

void GUIManager::removeUIComponent(IUIComponent* obj)
{
	auto it = std::find(this->x_ui_components.begin(), this->x_ui_components.end(), obj);
	if (it != this->x_ui_components.end())
		this->x_ui_components.erase(it);
}

void GUIManager::UpdateUIComponents()
{
	for (auto it = this->x_ui_components.begin(); it != this->x_ui_components.end(); it++) {
		(*it)->update();
	}

}

void GUIManager::onEvent(IEvent& event)
{
	for (auto it = this->x_ui_components.begin(); it != this->x_ui_components.end(); it++) {
		(*it)->onEvent(event);
	}
}

