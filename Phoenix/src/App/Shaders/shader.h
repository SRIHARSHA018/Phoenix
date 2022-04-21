#pragma once
#include "ShaderUtils.h"

struct ShaderDetails {
	const char* vertex_shader_file_path;
	const char* fragment_shader_file_path;
	unsigned int shader_program_id;
};

class Shader {
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader();
public:
	void useShaderProgram();
	unsigned int getShaderProgramId();
private:
	ShaderDetails x_shader_info;
private:
	void x_setupShaderProgram();
};
