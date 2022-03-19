#include "SpotLight.h"

SpotLight::SpotLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position, const glm::vec3& direction, unsigned int shaderProgramId)
	:ILight(ambient,diffuse,specular),x_position(position),x_direction(direction),x_shaderProgramId(shaderProgramId)
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
    UniformManager::getUniformManager()->setUniformVec3("u_spotLight.props.diffuse", this->x_shaderProgramId, glm::value_ptr(diffuse));
    UniformManager::getUniformManager()->setUniformVec3("u_spotLight.props.ambient", this->x_shaderProgramId, glm::value_ptr(ambient));
    UniformManager::getUniformManager()->setUniformVec3("u_spotLight.props.specular", this->x_shaderProgramId, glm::value_ptr(specular));
    UniformManager::getUniformManager()->setUniformVec3("u_spotLight.position", this->x_shaderProgramId, glm::value_ptr(this->x_position));
    UniformManager::getUniformManager()->setUniformVec3("u_spotLight.direction", this->x_shaderProgramId, glm::value_ptr(this->x_direction));
    UniformManager::getUniformManager()->setUniform("u_spotLight.attenuationProps.constant", this->x_shaderProgramId, 1.f);
    UniformManager::getUniformManager()->setUniform("u_spotLight.attenuationProps.linear", this->x_shaderProgramId, 0.09f);
    UniformManager::getUniformManager()->setUniform("u_spotLight.attenuationProps.quadratic", this->x_shaderProgramId, 0.032f);
    UniformManager::getUniformManager()->setUniform("u_spotLight.cutOff", this->x_shaderProgramId,glm::cos(glm::radians(12.5f)));
    UniformManager::getUniformManager()->setUniform("u_spotLight.outerCutOff", this->x_shaderProgramId,glm::cos(glm::radians(15.0f)));
}
