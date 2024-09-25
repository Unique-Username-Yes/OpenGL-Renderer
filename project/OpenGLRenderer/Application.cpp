#include "Application.hpp"
#include <span>
#include "shaders/ShaderHandler.hpp"

namespace OpenGLRenderer
{
    static void GLFWErrorCallback(int error, const char* description)
	{
		printf("GLFW Error ({0}): {1}", error, description);
	}

    Application::Application(const WindowProps& props)
    {
        if(int success = glfwInit(); !success)
        {
            std::runtime_error("GLFW Error: Could not initialize GLFW");
        }

        glfwSetErrorCallback(GLFWErrorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_Window);
        
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::runtime_error("Failed to initialize GLAD");
        }
    }

    void OpenGLRenderer::Application::ProcessInputs()
    {
        if(glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            m_Running = false;
    }

    void Application::Run()
    {
        ShaderHandler shaderHandler("/home/mmyes/Projects/OpenGL-Renderer/project/OpenGLRenderer/shaders/shaderSources/shader.vs", "/home/mmyes/Projects/OpenGL-Renderer/project/OpenGLRenderer/shaders/shaderSources/shader.fs");

        glViewport(0, 0, 800, 800);

        shaderHandler.Use();

        while(m_Running)
        {
            ProcessInputs();

            // Render
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for(Layer* layer: m_LayerStack)
            {
                layer->OnUpdate(glfwGetTime());
            }            

            // Buffer swap and IO
            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }
}
