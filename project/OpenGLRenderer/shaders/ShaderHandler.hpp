#pragma once

#include <glad/glad.h>
#include <string>

class ShaderHandler
{
    public:
        ShaderHandler(const std::string &vertexShaderSourcePath, const std::string &fragmentShaderSourcePath);

        inline void Bind() { glUseProgram(m_ProgramId); }
        inline void Unbind() { glUseProgram(0); }

        inline void SetFloat(const GLchar* uniformName, float f1) { glUniform1f(glGetUniformLocation(m_ProgramId, uniformName), f1); }
        inline void SetFloatV4(const GLchar* uniformName, float f1, float f2, float f3, float f4) { glUniform4f(glGetUniformLocation(m_ProgramId, uniformName), f1, f2, f3, f4); }

    public:
        unsigned int m_ProgramId;

    private:
        std::string ReadShaderSource(const std::string &filepath);
        unsigned int CompileShader(const char* source, GLenum shaderType);

};