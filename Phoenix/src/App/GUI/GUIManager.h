#pragma once
#include "IUIComponent.h"
#include <vector>

class GUIManager {
public:
	~GUIManager();
public:
	void addUIComponent(IUIComponent* obj);
	void removeUIComponent(IUIComponent* obj);
	void UpdateUIComponents();
	void onEvent(IEvent& event);
private:
	std::vector<IUIComponent*> x_uiComponents;
};