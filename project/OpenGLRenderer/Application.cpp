#include "Application.hpp"
#include <span>
#include "shaders/ShaderHandler.hpp"

namespace OpenGLRenderer
{
    Application::Application(const WindowProps& props)
    {
        m_Window = new Window{};
    }

    void Application::Run()
    {
        ShaderHandler shaderHandler("/home/mmyes/Projects/OpenGL-Renderer/project/OpenGLRenderer/shaders/shaderSources/shader.vs", "/home/mmyes/Projects/OpenGL-Renderer/project/OpenGLRenderer/shaders/shaderSources/shader.fs");

        glViewport(0, 0, 800, 800);

        shaderHandler.Use();

        while(m_Running)
        {
            m_Running = !m_Window->IsCloseEventTriggered();

            // Render
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for(Layer* layer: m_LayerStack)
            {
                layer->OnUpdate(m_Window->GetTime());
            }            

            m_Window->OnUpdate();
        }
    }
}
