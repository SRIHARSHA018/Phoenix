#include "shader.h"


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
	:x_shader_info({ vertexShaderPath,fragmentShaderPath })
{
	x_setupShaderProgram();
}

Shader::~Shader()
{
	glDeleteShader(this->x_shader_info.shader_program_id);
}

void Shader::useShaderProgram()
{
	glUseProgram(this->x_shader_info.shader_program_id);
}

unsigned int Shader::getShaderProgramId()
{
	return this->x_shader_info.shader_program_id;
}

void Shader::x_setupShaderProgram()
{
	this->x_shader_info.shader_program_id = ShaderUtils::buildShaderProgram(
		ShaderUtils::buildShaderFromFile(this->x_shader_info.vertex_shader_file_path, GL_VERTEX_SHADER),
		ShaderUtils::buildShaderFromFile(this->x_shader_info.fragment_shader_file_path, GL_FRAGMENT_SHADER)
	);

}
