#pragma once
#include "ILight.h"
#include "Shaders/UniformManager.h"

class DirectionalLight :public ILight
{
public:
	DirectionalLight(unsigned int shader_program_id);
	DirectionalLight(const glm::vec3& ambient,
		const glm::vec3& diffuse,
		const glm::vec3& specular,
		const glm::vec3& direction, unsigned int shader_program_id);
	~DirectionalLight();

public:
	virtual void update() override;
	virtual void onEvent(IEvent& event) override;
private:
	void x_updateUniforms();
private:
	glm::vec3 x_direction;
	unsigned int x_shader_program_id;
};