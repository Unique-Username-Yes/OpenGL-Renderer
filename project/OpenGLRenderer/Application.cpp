#include "Application.h"
#include <span>
#include "shaders/ShaderHandler.h"

namespace OpenGLRenderer
{
    static void GLFWErrorCallback(int error, const char* description)
	{
		printf("GLFW Error ({0}): {1}", error, description);
	}

    static void bindVerticesToVBO(std::span<const float> vertices)
    {
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW);
    }

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
        
        unsigned int VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glViewport(0, 0, 800, 800);

        shaderHandler.Use();

        while(m_Running)
        {
            ProcessInputs();

            // Render
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 12);

            // Buffer swap and IO
            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }
}