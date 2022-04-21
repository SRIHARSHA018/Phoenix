#pragma once
#include "ILight.h"
#include "Shaders/UniformManager.h"

class PointLight :
	public ILight
{
public:
	PointLight(unsigned int shader_program_id);
	PointLight(const glm::vec3& ambient,
		const glm::vec3& diffuse,
		const glm::vec3& specular,
		const glm::vec3& position,
		unsigned int shader_program_id);
	~PointLight();

public:
	virtual void update() override;
	virtual void onEvent(IEvent& event) override;

public:
	inline void setPostion(const glm::vec3& position) { this->x_position = position; }

private:
	glm::vec3 x_position;
	unsigned int x_shader_program_id;

private:
	void x_updateUniforms();
};

