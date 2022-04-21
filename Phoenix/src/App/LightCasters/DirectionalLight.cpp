#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(unsigned int shader_program_id)
	:x_direction(glm::vec3(0.f, 0.f, 1.f)), x_shader_program_id(shader_program_id), ILight()
{
}

DirectionalLight::DirectionalLight(const glm::vec3& ambient,
	const glm::vec3& diffuse,
	const glm::vec3& specular,
	const glm::vec3& direction,
	unsigned int shader_program_id)
	: ILight(ambient, diffuse, specular), x_direction(direction), x_shader_program_id(shader_program_id)
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
	UniformManager::get()->setUniformVec3("u_dirLight.props.diffuse", this->x_shader_program_id, glm::value_ptr(light_properties.diffuse));
	UniformManager::get()->setUniformVec3("u_dirLight.props.ambient", this->x_shader_program_id, glm::value_ptr(light_properties.ambient));
	UniformManager::get()->setUniformVec3("u_dirLight.props.specular", this->x_shader_program_id, glm::value_ptr(light_properties.specular));
	UniformManager::get()->setUniformVec3("u_dirLight.direction", this->x_shader_program_id, glm::value_ptr(this->x_direction));
	UniformManager::get()->setUniformVec3("u_dirLight.direction", this->x_shader_program_id, glm::value_ptr(this->x_direction));
}
