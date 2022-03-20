#pragma once
#include "ILight.h"
#include "UniformManager.h"

class DirectionalLight :public ILight
{
public:
	DirectionalLight(unsigned int shaderProgramId);
	DirectionalLight(const glm::vec3& ambient,
		const glm::vec3& diffuse,
		const glm::vec3& specular,
		const glm::vec3& direction,unsigned int shaderProgramId);
	~DirectionalLight();

public:
	virtual void update() override;
	virtual void onEvent(IEvent& event) override;
private:
	void x_updateUniforms();
private:
	glm::vec3 x_direction;
	unsigned int x_shaderProgramId;
};