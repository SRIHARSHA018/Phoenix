#include "DirectionalLight.h"


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
	UniformManager::getUniformManager()->setUniformVec3("u_dirLight.props.diffuse", this->x_shaderProgramId, glm::value_ptr(diffuse));
	UniformManager::getUniformManager()->setUniformVec3("u_dirLight.props.ambient", this->x_shaderProgramId, glm::value_ptr(ambient));
	UniformManager::getUniformManager()->setUniformVec3("u_dirLight.props.specular", this->x_shaderProgramId, glm::value_ptr(specular));
	UniformManager::getUniformManager()->setUniformVec3("u_dirLight.direction", this->x_shaderProgramId,glm::value_ptr(this->x_direction));
}
