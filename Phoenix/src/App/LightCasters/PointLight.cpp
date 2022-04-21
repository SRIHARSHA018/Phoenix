#include "PointLight.h"

PointLight::PointLight(unsigned int shader_program_id)
	:x_position(glm::vec3(0.f)),
	ILight(),
	x_shader_program_id(shader_program_id)
{
}

PointLight::PointLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position, unsigned int shader_program_id)
	:ILight(ambient, diffuse, specular),
	x_position(position),
	x_shader_program_id(shader_program_id)
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
	UniformManager::get()->setUniformVec3("u_pointLight.props.diffuse", this->x_shader_program_id, glm::value_ptr(light_properties.diffuse));
	UniformManager::get()->setUniformVec3("u_pointLight.props.ambient", this->x_shader_program_id, glm::value_ptr(light_properties.ambient));
	UniformManager::get()->setUniformVec3("u_pointLight.props.specular", this->x_shader_program_id, glm::value_ptr(light_properties.specular));
	UniformManager::get()->setUniformVec3("u_pointLight.position", this->x_shader_program_id, glm::value_ptr(this->x_position));
	UniformManager::get()->setUniform("u_pointLight.attenuationProps.constant", this->x_shader_program_id, light_properties.attenuation.x);
	UniformManager::get()->setUniform("u_pointLight.attenuationProps.linear", this->x_shader_program_id, light_properties.attenuation.y);
	UniformManager::get()->setUniform("u_pointLight.attenuationProps.quadratic", this->x_shader_program_id, light_properties.attenuation.z);

}
