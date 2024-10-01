#pragma once

#include <glad/glad.h>
#include "OpenGLRenderer/Layer.hpp"

class MainLayer: public OpenGLRenderer::Layer
{
    public:
        MainLayer(const std::string& layerName): OpenGLRenderer::Layer(layerName) 
        { 
            m_LayerName = layerName;
            MainLayer(); 
        }
        MainLayer(): m_LayerName{"Layer"}
        {
            const float vertices[] = 
            {
                -0.25f, 0.0f, 0.0f,
                0.25f, 0.0f, 0.0f,
                0.0f, -0.5f, 0.0f,

                -0.5f, -0.5f, 0.0f,
                -0.25f, 0.0f, 0.0f,
                0.0f, -0.5f, 0.0f,

                0.0f, -0.5f, 0.0f,
                0.25f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f,

                -0.25f, 0.0f, 0.0f,
                0.0f,  0.5f, 0.0f,
                0.25f, 0.0f, 0.0f  
            };

            const unsigned int indices[] = 
            {
                0, 1, 3,
                1, 2, 3
            };

            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);

            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }

        void OnUpdate(float timestep) override
        {
            glBindVertexArray(m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 12);
        }

        void OnAttach() override
        {
        }

        void OnDetach() override
        {

        }

        void OnEvent(OpenGLRenderer::Event &event) override 
        {
        }

    private:
        unsigned int m_VAO, m_VBO;
        std::string m_LayerName;
};