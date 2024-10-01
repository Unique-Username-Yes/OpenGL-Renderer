#include "Application.hpp"
#include <span>
#include "shaders/ShaderHandler.hpp"
#include <functional>

namespace OpenGLRenderer
{
    Application::Application(const WindowProps& props)
    {
        m_Window = std::unique_ptr<Window>(new Window{});
        m_Window->SetEventCallbackFn(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    void Application::OnEvent(Event &event)
    {
        if(event.GetEventType() == EventType::WindowClose)
            m_Running = false;

        for(Layer* layer: m_LayerStack)
        {
            layer->OnEvent(event);
        }
    }

    void Application::Run()
    {
        ShaderHandler shaderHandler("/home/mmyes/Projects/OpenGL-Renderer/project/OpenGLRenderer/shaders/shaderSources/shader.vs", "/home/mmyes/Projects/OpenGL-Renderer/project/OpenGLRenderer/shaders/shaderSources/shader.fs");

        glViewport(0, 0, 800, 800);

        shaderHandler.Use();

        while(m_Running)
        {
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
