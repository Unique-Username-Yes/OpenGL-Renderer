#include <fstream>
#include <sstream>
#include <iostream>
#include "ShaderHandler.h"

ShaderHandler::ShaderHandler(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath)
{
    auto vShaderCode = ReadShaderSource(vertexShaderSourcePath);
    auto fShaderCode = ReadShaderSource(fragmentShaderSourcePath);

    auto vShader = CompileShader(vShaderCode.c_str(), GL_VERTEX_SHADER);
    auto fShader = CompileShader(fShaderCode.c_str(), GL_FRAGMENT_SHADER);

    programId = glCreateProgram();

    glAttachShader(programId, vShader);
    glAttachShader(programId, fShader);

    glLinkProgram(programId);
    int success;
    char infoLog[512];
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::LINKING_ERROR " << infoLog << std::endl;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void ShaderHandler::Use()
{
    glUseProgram(programId);
}

std::string ShaderHandler::ReadShaderSource(const char* filepath)
{
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream buffer;

    try
    {
        shaderFile.open(filepath);
        buffer << shaderFile.rdbuf();
        shaderFile.close();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FAILED_TO_READ" << std::endl;
    }    

    return buffer.str();
}

unsigned int ShaderHandler::CompileShader(const char *source, GLenum shaderType)
{
    unsigned int shaderId;
    shaderId = glCreateShader(shaderType);

    glShaderSource(shaderId, 1, &source, NULL);
    glCompileShader(shaderId);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED" << infoLog << std::endl;
    }

    return shaderId;
}