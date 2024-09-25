#pragma once

#include <glad/glad.h>
#include <string>

class ShaderHandler
{
    public:
        ShaderHandler(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);
        void Use();

        inline void SetFloat(const GLchar* uniformName, float f1) { glUniform1f(glGetUniformLocation(programId, uniformName), f1); }
        inline void SetFloatV4(const GLchar* uniformName, float f1, float f2, float f3, float f4) { glUniform4f(glGetUniformLocation(programId, uniformName), f1, f2, f3, f4); }

    public:
        unsigned int programId;

    private:
        std::string ReadShaderSource(const char* filepath);
        unsigned int CompileShader(const char *source, GLenum shaderType);

};