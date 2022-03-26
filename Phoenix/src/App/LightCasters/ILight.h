#pragma once
#include "Scene/SceneObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct LightProps {
	glm::vec3 ambient = glm::vec3(0.1f);
	glm::vec3 diffuse = glm::vec3(1.f);
	glm::vec3 specular = glm::vec3(1.f);

	//attenuation x=constant, y=linear z=quadratic
	glm::vec3 attenuation = glm::vec3(1.f, 0.09f, 0.032f);
};


class ILight :public ISceneObject
{
public:
	ILight() :properties(LightProps()) {}
	ILight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
		:properties({ ambient,diffuse,specular }) {}

	virtual ~ILight() {}

public:
	virtual void update() = 0;
	virtual void onEvent(IEvent& event) = 0;
public:
	LightProps properties;
};