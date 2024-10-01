#include "Window.hpp"
#include <stdexcept>
#include "Events/ApplicationEvent.hpp"

namespace OpenGLRenderer
{
    static void GLFWErrorCallback(int error, const char* description)
	{
		printf("GLFW Error ({0}): {1}", error, description);
	}

    Window::Window(const WindowProps& props)
    {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

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

        glfwSetWindowUserPointer(m_Window, &m_Data);

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
        {
            auto data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);  
        });
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
}
