#include "SpotLight.h"

SpotLight::SpotLight(unsigned int shaderProgramId)
	:ILight(), x_shaderProgramId(shaderProgramId), x_position(glm::vec3(0.f)),
	x_direction(glm::vec3(0.f, 0.f, 1.f)), x_outerConeAngle(15.f), x_innerConeAngle(12.5f)
{
}

SpotLight::SpotLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position, const glm::vec3& direction, unsigned int shaderProgramId)
	: ILight(ambient, diffuse, specular), x_position(position), x_direction(direction), x_shaderProgramId(shaderProgramId),
	x_outerConeAngle(15.f), x_innerConeAngle(12.5f)
{
}

SpotLight::~SpotLight()
{
}

void SpotLight::update()
{
	this->x_updateUniforms();
}

void SpotLight::onEvent(IEvent& event)
{
}

void SpotLight::x_updateUniforms()
{
	UniformManager::get()->setUniformVec3("u_spotLight.props.diffuse", this->x_shaderProgramId, glm::value_ptr(properties.diffuse));
	UniformManager::get()->setUniformVec3("u_spotLight.props.ambient", this->x_shaderProgramId, glm::value_ptr(properties.ambient));
	UniformManager::get()->setUniformVec3("u_spotLight.props.specular", this->x_shaderProgramId, glm::value_ptr(properties.specular));
	UniformManager::get()->setUniformVec3("u_spotLight.position", this->x_shaderProgramId, glm::value_ptr(this->x_position));
	UniformManager::get()->setUniformVec3("u_spotLight.direction", this->x_shaderProgramId, glm::value_ptr(this->x_direction));
	UniformManager::get()->setUniform("u_spotLight.attenuationProps.constant", this->x_shaderProgramId, properties.attenuation.x);
	UniformManager::get()->setUniform("u_spotLight.attenuationProps.linear", this->x_shaderProgramId, properties.attenuation.y);
	UniformManager::get()->setUniform("u_spotLight.attenuationProps.quadratic", this->x_shaderProgramId, properties.attenuation.z);
	UniformManager::get()->setUniform("u_spotLight.cutOff", this->x_shaderProgramId, glm::cos(glm::radians(this->x_innerConeAngle)));
	UniformManager::get()->setUniform("u_spotLight.outerCutOff", this->x_shaderProgramId, glm::cos(glm::radians(this->x_outerConeAngle)));
}
