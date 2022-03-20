#include "PointLight.h"

PointLight::PointLight(unsigned int shaderProgramId)
    :x_position(glm::vec3(0.f)),
    ILight(),
    x_shaderProgramId(shaderProgramId)
{
}

PointLight::PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position, unsigned int shaderProgramId)
	:ILight(ambient, diffuse, specular),
    x_position(position),
    x_shaderProgramId(shaderProgramId)
{
}

PointLight::~PointLight()
{
}

void PointLight::update()
{
	this->x_updateUniforms();
}

void PointLight::onEvent(IEvent& event)
{

}

void PointLight::x_updateUniforms()
{
    UniformManager::getUniformManager()->setUniformVec3("u_pointLight.props.diffuse", this->x_shaderProgramId, glm::value_ptr(properties.diffuse));
    UniformManager::getUniformManager()->setUniformVec3("u_pointLight.props.ambient", this->x_shaderProgramId, glm::value_ptr(properties.ambient));
    UniformManager::getUniformManager()->setUniformVec3("u_pointLight.props.specular", this->x_shaderProgramId, glm::value_ptr(properties.specular));
    UniformManager::getUniformManager()->setUniformVec3("u_pointLight.position", this->x_shaderProgramId, glm::value_ptr(this->x_position));
    UniformManager::getUniformManager()->setUniform("u_pointLight.attenuationProps.constant", this->x_shaderProgramId,properties.attenuation.x);
    UniformManager::getUniformManager()->setUniform("u_pointLight.attenuationProps.linear", this->x_shaderProgramId,properties.attenuation.y);
    UniformManager::getUniformManager()->setUniform("u_pointLight.attenuationProps.quadratic", this->x_shaderProgramId,properties.attenuation.z);

}
