#include "Window.hpp"
#include <stdexcept>
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"

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

        m_Window = unique_glfwwindow_ptr(glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr), Window::GLFWwindowDeleter);

        glfwMakeContextCurrent(m_Window.get());

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::runtime_error("Failed to initialize GLAD");
        }

        glfwSetWindowUserPointer(m_Window.get(), &m_Data);

        glfwSetWindowCloseCallback(m_Window.get(), [](GLFWwindow* window)
        {
            auto data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.m_EventCallback(event);  
        });

        glfwSetKeyCallback(m_Window.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            auto data = *(WindowData*)glfwGetWindowUserPointer(window);
            if(action == GLFW_PRESS)
            {
                // Might actually be triggered by the glfwSetCharCallback
                KeyTypedEvent event { key };
                data.m_EventCallback(event);
            }
            else if(action == GLFW_RELEASE)
            {
                KeyUpEvent event { key };
                data.m_EventCallback(event);
            }
            else if(action == GLFW_REPEAT)
            {
                KeyDownEvent event { key, 1};
                data.m_EventCallback(event);
            }
        });
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window.get());
    }
}
