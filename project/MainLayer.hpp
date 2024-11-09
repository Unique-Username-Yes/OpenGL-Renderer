#pragma once

#include <glad/glad.h>
#include "OpenGLRenderer/Layer.hpp"
#include "OpenGLRenderer/shaders/ShaderHandler.hpp"
#include "stb_image.h"
#include "OpenGLRenderer/Renderer/Texture2D.hpp"
#include "OpenGLRenderer/Events/KeyEvent.hpp"
#include "OpenGLRenderer/Events/KeyCodes.hpp"

class MainLayer: public OpenGLRenderer::Layer
{
    public:
        MainLayer(const std::string& layerName = "Layer"): 
            m_LayerName{layerName}, 
            m_WallTexture{"/home/mmyes/Projects/OpenGL-Renderer/assets/textures/wall.jpg"},
            m_FaceTexture{"/home/mmyes/Projects/OpenGL-Renderer/assets/textures/awesomeface.png"}
        {
            const float vertices[] = 
            {
                 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
                 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
            };

            const unsigned int indices[] = 
            {
                0, 1, 3,
                1, 2, 3
            };

            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_EBO);

            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));

            ShaderHandler shaderHandler {"/home/mmyes/Projects/OpenGL-Renderer/project/OpenGLRenderer/shaders/shaderSources/shader.vs", "/home/mmyes/Projects/OpenGL-Renderer/project/OpenGLRenderer/shaders/shaderSources/shader.fs"};
            shaderHandler.Bind();

            // Texture stuff
            m_WallTexture.Bind(GL_TEXTURE0);
            m_FaceTexture.Bind(GL_TEXTURE1);

            glUniform1i(glGetUniformLocation(shaderHandler.m_ProgramId, "textureSource"), 0);
            glUniform1i(glGetUniformLocation(shaderHandler.m_ProgramId, "textureSource2"), 1);
        }

        void OnUpdate(float timestep) override
        {
            glBindVertexArray(m_VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        void OnAttach() override
        {
        }

        void OnDetach() override
        {

        }

        void OnEvent(OpenGLRenderer::Event &event) override 
        {
            if(event.GetEventType() == OpenGLRenderer::EventType::KeyTyped)
            {
                auto keyEvent = static_cast<OpenGLRenderer::KeyTypedEvent&>(event);
                std::cout << keyEvent.ToString();
                if(keyEvent.GetKeyCode() == OGLR_KEY_E)
                {
                    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                }
                else
                {
                    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                }
            }
        }

    private:
        unsigned int m_VAO, m_VBO, m_EBO;
        std::string m_LayerName;
        OpenGLRenderer::Texture2D m_WallTexture, m_FaceTexture;
};