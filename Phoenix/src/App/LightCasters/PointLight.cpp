#include "PointLight.h"

PointLight::PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position, unsigned int shaderProgramId)
	:ILight(ambient, diffuse, specular), x_position(position),x_shaderProgramId(shaderProgramId)
{
}

PointLight::~PointLight()
{
}

void PointLight::Update()
{
	this->x_updateUniforms();
}

void PointLight::onEvent(IEvent& event)
{

}

void PointLight::x_updateUniforms()
{
    UniformManager::getUniformManager()->setUniformVec3("u_pointLight.props.diffuse", this->x_shaderProgramId, glm::value_ptr(diffuse));
    UniformManager::getUniformManager()->setUniformVec3("u_pointLight.props.ambient", this->x_shaderProgramId, glm::value_ptr(ambient));
    UniformManager::getUniformManager()->setUniformVec3("u_pointLight.props.specular", this->x_shaderProgramId, glm::value_ptr(specular));
    UniformManager::getUniformManager()->setUniformVec3("u_pointLight.position", this->x_shaderProgramId, glm::value_ptr(this->x_position));
    UniformManager::getUniformManager()->setUniform("u_pointLight.attenuationProps.constant", this->x_shaderProgramId,1.f);
    UniformManager::getUniformManager()->setUniform("u_pointLight.attenuationProps.linear", this->x_shaderProgramId,0.09f);
    UniformManager::getUniformManager()->setUniform("u_pointLight.attenuationProps.quadratic", this->x_shaderProgramId,0.032f);

}
