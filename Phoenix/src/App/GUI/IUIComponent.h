#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Events/Event.h"

enum class UIElementType {
	BUTTON
};

struct UIElementProps {
	float x, y;
	float width, height;
	glm::vec3 color;
};

class IUIComponent
{
public:
	virtual ~IUIComponent() {}
	virtual void draw() = 0;
	virtual void onEvent(IEvent& event) = 0;
	virtual void update() = 0;
};