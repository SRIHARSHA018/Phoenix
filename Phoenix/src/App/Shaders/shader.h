#pragma once
#include "ShaderUtils.h"

struct shaderDetails {
    const char* vertexShaderFilePath;
    const char* fragmentShaderFilePath;
    unsigned int shaderProgramId;
};

class Shader {
public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~Shader();
public:
    void useShaderProgram();
    unsigned int getShaderProgramId();
private:
    shaderDetails x_shaderInfo;
private:
    void x_setupShaderProgram();
};
