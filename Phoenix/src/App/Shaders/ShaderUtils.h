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
		static unsigned int  buildShaderFromFile(const char* filepath, GLenum shaderType);
		static unsigned int  buildShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId);
private:
		static void x_checkErrors(unsigned int id,CheckType type);
};