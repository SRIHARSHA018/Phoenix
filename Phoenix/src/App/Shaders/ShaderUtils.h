#pragma once
#include <GLEW/glew.h>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>


enum class CheckType
{
	SHADER_IV,
	PROGRAM_IV,
};

class ShaderUtils {
public:
	static unsigned int  buildShaderFromFile(const char* file_path, GLenum shader_type);
	static unsigned int  buildShaderProgram(unsigned int vertex_shader_id, unsigned int fragment_shader_id);
private:
	static void x_checkErrors(unsigned int id, CheckType type);
};