#include "ShaderUtils.h"

unsigned int  ShaderUtils::buildShaderFromFile(const char* filepath, GLenum shaderType)
{
    std::ifstream shaderFile;
    std::stringstream shaderCodeStream;
    std::string shaderCodestr;
    const char* shaderCode;
    unsigned int shaderId;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(filepath);
        shaderCodeStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCodestr = shaderCodeStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
    shaderCode = shaderCodestr.c_str();
    shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    x_checkErrors(shaderId,CheckType::SHADER_IV);
    return shaderId;
}

unsigned int ShaderUtils::buildShaderProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId)
{
    // shader Program
    unsigned int shaderProgramId;
    shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram (shaderProgramId);

    //TODO:Cleanup
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    x_checkErrors(shaderProgramId, CheckType::PROGRAM_IV);
    return shaderProgramId;
}

void ShaderUtils::x_checkErrors(unsigned int id, CheckType type)
{
    int success;
    char infoLog[1024];
    switch (type)
    {
    case CheckType::SHADER_IV: {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
        break;
    }
    case CheckType::PROGRAM_IV: {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " <<"\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
        break;
    }

    default:

        break;
    }
}
