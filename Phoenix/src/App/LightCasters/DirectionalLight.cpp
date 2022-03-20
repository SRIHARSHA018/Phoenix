#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(unsigned int shaderProgramId)
	:x_direction(glm::vec3(0.f,0.f,1.f)),x_shaderProgramId(shaderProgramId),ILight()
{
}

DirectionalLight::DirectionalLight(const glm::vec3& ambient,
								   const glm::vec3& diffuse,
								   const glm::vec3& specular,
								   const glm::vec3& direction,
								   unsigned int shaderProgramId)
	:ILight(ambient, diffuse, specular), x_direction(direction),x_shaderProgramId(shaderProgramId)
{
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::update()
{
	this->x_updateUniforms();
}

void DirectionalLight::onEvent(IEvent& event)
{

}

void DirectionalLight::x_updateUniforms()
{	
	UniformManager::getUniformManager()->setUniformVec3("u_dirLight.props.diffuse", this->x_shaderProgramId, glm::value_ptr(properties.diffuse));
	UniformManager::getUniformManager()->setUniformVec3("u_dirLight.props.ambient", this->x_shaderProgramId, glm::value_ptr(properties.ambient));
	UniformManager::getUniformManager()->setUniformVec3("u_dirLight.props.specular", this->x_shaderProgramId, glm::value_ptr(properties.specular));
	UniformManager::getUniformManager()->setUniformVec3("u_dirLight.direction", this->x_shaderProgramId,glm::value_ptr(this->x_direction));
}
