#include "shader.h"


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) 
    :x_shaderInfo({vertexShaderPath,fragmentShaderPath})
{
    x_setupShaderProgram();
}

Shader::~Shader()
{
    glDeleteShader(this->x_shaderInfo.shaderProgramId);
}

void Shader::useShaderProgram()
{
    glUseProgram(this->x_shaderInfo.shaderProgramId);
}

unsigned int Shader::getShaderProgramId()
{
    return this->x_shaderInfo.shaderProgramId;
}

void Shader::x_setupShaderProgram()
{
    this->x_shaderInfo.shaderProgramId = ShaderUtils::buildShaderProgram(
        ShaderUtils::buildShaderFromFile(this->x_shaderInfo.vertexShaderFilePath, GL_VERTEX_SHADER),
        ShaderUtils::buildShaderFromFile(this->x_shaderInfo.fragmentShaderFilePath, GL_FRAGMENT_SHADER)
    );

}
