#include "UniformManager.h"



#define __IMPL_SET_UNIFORM(count,type,name,shaderProgramId,...) \
    glUniform##count##type(this->x_getUniformLocation(name, shaderProgramId), __VA_ARGS__);

UniformManager *UniformManager::x_manager = nullptr;
UniformManager *UniformManager::getUniformManager()
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
    if(this->x_manager!=NULL)
        delete x_manager;
}

unsigned int UniformManager::x_getUniformLocation(const std::string &uniformName, unsigned int shaderProgramId)
{
    if (this->x_uniformLocationCache.find(uniformName) != this->x_uniformLocationCache.end())
    {
        return x_uniformLocationCache[uniformName];
    }
    x_uniformLocationCache[uniformName] = glGetUniformLocation(shaderProgramId, uniformName.c_str());
    return x_uniformLocationCache[uniformName];
}

void UniformManager::setUniform(const std::string &name, unsigned int shaderProgramId, float v0, float v1, float v2)
{
    __IMPL_SET_UNIFORM(3, f, name, shaderProgramId, v0,v1,v2);
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
    __IMPL_SET_UNIFORM(3, fv, name, shaderProgramId, 1,value);
}
