#include "Window.hpp"
#include <stdexcept>

namespace OpenGLRenderer
{
    static void GLFWErrorCallback(int error, const char* description)
	{
		printf("GLFW Error ({0}): {1}", error, description);
	}

    Window::Window(const WindowProps& props)
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

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
}
