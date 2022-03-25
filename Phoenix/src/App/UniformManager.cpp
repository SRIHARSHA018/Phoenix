#include "UniformManager.h"



#define __IMPL_SET_UNIFORM(count,type,name,shaderProgramId,...) \
    glUniform##count##type(this->x_getUniformLocation(name, shaderProgramId), __VA_ARGS__);

UniformManager* UniformManager::x_manager = nullptr;
UniformManager* UniformManager::getUniformManager()
{
	if (x_manager == nullptr)
	{
		x_manager = new UniformManager();
		return x_manager;
	}
	return x_manager;
}

UniformManager::~UniformManager()
{
	if (this->x_manager != NULL)
		delete x_manager;
}

unsigned int UniformManager::x_getUniformLocation(const std::string& uniformName, unsigned int shaderProgramId)
{
	if (this->x_shaderUniformsCache.find(shaderProgramId) == this->x_shaderUniformsCache.end()) {
		this->x_shaderUniformsCache[shaderProgramId] = std::unordered_map< std::string, unsigned int>();
	}
	if (this->x_shaderUniformsCache[shaderProgramId].find(uniformName) != this->x_shaderUniformsCache[shaderProgramId].end())
	{
		return this->x_shaderUniformsCache[shaderProgramId][uniformName];
	}
	this->x_shaderUniformsCache[shaderProgramId][uniformName] = glGetUniformLocation(shaderProgramId, uniformName.c_str());
	return this->x_shaderUniformsCache[shaderProgramId][uniformName];
}

void UniformManager::setUniform(const std::string& name, unsigned int shaderProgramId, float v0, float v1, float v2)
{
	__IMPL_SET_UNIFORM(3, f, name, shaderProgramId, v0, v1, v2);
}
void UniformManager::setUniform(const std::string& name, unsigned int shaderProgramId, float v0, float v1, float v2, float v3)
{
	__IMPL_SET_UNIFORM(4, f, name, shaderProgramId, v0, v1, v2, v3);
}

void UniformManager::setUniform(const std::string& name, unsigned int shaderProgramId, int v0)
{
	__IMPL_SET_UNIFORM(1, i, name, shaderProgramId, v0);
}

void UniformManager::setUniform(const std::string& name, unsigned int shaderProgramId, float v0)
{
	__IMPL_SET_UNIFORM(1, f, name, shaderProgramId, v0);
}

void UniformManager::setUniformMatrix4fv(const std::string& name, unsigned int shaderProgramId, const float* value)
{
	__IMPL_SET_UNIFORM(Matrix4, fv, name, shaderProgramId, 1, GL_FALSE, value);
}

void UniformManager::setUniformVec3(const std::string& name, unsigned int shaderProgramId, const float* value)
{
	__IMPL_SET_UNIFORM(3, fv, name, shaderProgramId, 1, value);
}
