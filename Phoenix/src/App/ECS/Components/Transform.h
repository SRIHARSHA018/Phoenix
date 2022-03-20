#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Component.h"

struct Transform:public IComponent
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};
