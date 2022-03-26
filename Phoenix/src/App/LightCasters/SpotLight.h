#pragma once
#include "ILight.h"
#include "Shaders/UniformManager.h"

class SpotLight :
	public ILight
{
public:
	SpotLight(unsigned int shaderProgramId);
	SpotLight(const glm::vec3& ambient,
		const glm::vec3& diffuse,
		const glm::vec3& specular,
		const glm::vec3& position,
		const glm::vec3& direction,
		unsigned int shaderProgramId);
	~SpotLight();

public:
	virtual void update() override;
	virtual void onEvent(IEvent& event) override;

public:
	inline void setPostion(const glm::vec3& position) { this->x_position = position; }
	inline void setDirection(const glm::vec3& direction) { this->x_direction = direction; }
	inline void setOuterConeAngle(const float& angle) { this->x_outerConeAngle = angle; }
	inline void setInnerConeAngle(const float& angle) { this->x_innerConeAngle = angle; }

private:
	glm::vec3 x_position;
	glm::vec3 x_direction;
	float x_outerConeAngle;
	float x_innerConeAngle;
	unsigned int x_shaderProgramId;

private:
	void x_updateUniforms();
};

