#include "UniformManager.h"



#define __IMPL_SET_UNIFORM(count,type,name,shader_program_id,...) \
    glUniform##count##type(this->x_getUniformLocation(name, shader_program_id), __VA_ARGS__);

std::shared_ptr<UniformManager> UniformManager::x_instance = NULL;


std::shared_ptr<UniformManager>& UniformManager::get()
{
	if (x_instance != NULL) return x_instance;
	x_instance = std::shared_ptr<UniformManager>(new UniformManager());
	return x_instance;
}

UniformManager::~UniformManager()
{
}

unsigned int UniformManager::x_getUniformLocation(const std::string& uniformName, unsigned int shader_program_id)
{
	if (this->x_shader_uniforms_cache.find(shader_program_id) == this->x_shader_uniforms_cache.end()) {
		this->x_shader_uniforms_cache[shader_program_id] = std::unordered_map< std::string, unsigned int>();
	}
	if (this->x_shader_uniforms_cache[shader_program_id].find(uniformName) != this->x_shader_uniforms_cache[shader_program_id].end())
	{
		return this->x_shader_uniforms_cache[shader_program_id][uniformName];
	}
	this->x_shader_uniforms_cache[shader_program_id][uniformName] = glGetUniformLocation(shader_program_id, uniformName.c_str());
	return this->x_shader_uniforms_cache[shader_program_id][uniformName];
}

void UniformManager::setUniform(const std::string& name, unsigned int shader_program_id, float v0, float v1, float v2)
{
	__IMPL_SET_UNIFORM(3, f, name, shader_program_id, v0, v1, v2);
}
void UniformManager::setUniform(const std::string& name, unsigned int shader_program_id, float v0, float v1, float v2, float v3)
{
	__IMPL_SET_UNIFORM(4, f, name, shader_program_id, v0, v1, v2, v3);
}

void UniformManager::setUniform(const std::string& name, unsigned int shader_program_id, int v0)
{
	__IMPL_SET_UNIFORM(1, i, name, shader_program_id, v0);
}

void UniformManager::setUniform(const std::string& name, unsigned int shader_program_id, float v0)
{
	__IMPL_SET_UNIFORM(1, f, name, shader_program_id, v0);
}

void UniformManager::setUniformMatrix4fv(const std::string& name, unsigned int shader_program_id, const float* value)
{
	__IMPL_SET_UNIFORM(Matrix4, fv, name, shader_program_id, 1, GL_FALSE, value);
}

void UniformManager::setUniformVec3(const std::string& name, unsigned int shader_program_id, const float* value)
{
	__IMPL_SET_UNIFORM(3, fv, name, shader_program_id, 1, value);
}
