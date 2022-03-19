#pragma once
#include "SceneObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ILight:public ISceneObject 
{
public:
	ILight(const glm::vec3& ambient,const glm::vec3& diffuse, const glm::vec3& specular)
		:diffuse(diffuse),ambient(ambient),specular(specular){}
	virtual ~ILight() {}
	virtual void update() = 0;
	virtual void onEvent(IEvent& event) = 0;
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};