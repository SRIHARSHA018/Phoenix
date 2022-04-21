#include "SpotLight.h"

SpotLight::SpotLight(unsigned int shader_program_id)
	:ILight(), x_shader_program_id(shader_program_id), x_position(glm::vec3(0.f)),
	x_direction(glm::vec3(0.f, 0.f, 1.f)), x_outer_cone_angle(15.f), x_inner_cone_angle(12.5f)
{
}

SpotLight::SpotLight(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position, const glm::vec3& direction, unsigned int shader_program_id)
	: ILight(ambient, diffuse, specular), x_position(position), x_direction(direction), x_shader_program_id(shader_program_id),
	x_outer_cone_angle(15.f), x_inner_cone_angle(12.5f)
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
	UniformManager::get()->setUniformVec3("u_spotLight.props.diffuse", this->x_shader_program_id, glm::value_ptr(light_properties.diffuse));
	UniformManager::get()->setUniformVec3("u_spotLight.props.ambient", this->x_shader_program_id, glm::value_ptr(light_properties.ambient));
	UniformManager::get()->setUniformVec3("u_spotLight.props.specular", this->x_shader_program_id, glm::value_ptr(light_properties.specular));
	UniformManager::get()->setUniformVec3("u_spotLight.position", this->x_shader_program_id, glm::value_ptr(this->x_position));
	UniformManager::get()->setUniformVec3("u_spotLight.direction", this->x_shader_program_id, glm::value_ptr(this->x_direction));
	UniformManager::get()->setUniform("u_spotLight.attenuationProps.constant", this->x_shader_program_id, light_properties.attenuation.x);
	UniformManager::get()->setUniform("u_spotLight.attenuationProps.linear", this->x_shader_program_id, light_properties.attenuation.y);
	UniformManager::get()->setUniform("u_spotLight.attenuationProps.quadratic", this->x_shader_program_id, light_properties.attenuation.z);
	UniformManager::get()->setUniform("u_spotLight.cutOff", this->x_shader_program_id, glm::cos(glm::radians(this->x_inner_cone_angle)));
	UniformManager::get()->setUniform("u_spotLight.outerCutOff", this->x_shader_program_id, glm::cos(glm::radians(this->x_outer_cone_angle)));
}
