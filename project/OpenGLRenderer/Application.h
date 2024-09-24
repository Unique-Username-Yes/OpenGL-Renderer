#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <string>

namespace OpenGLRenderer 
{
    struct WindowProps
    {
        std::string Title{};
        unsigned int Width{};
        unsigned int Height{};

        WindowProps(const std::string& title = "OpenGL Renderer",
                    unsigned int width = 800,
                    unsigned int height = 800)
            : Title(title), Width(width), Height(height) {}
    };

    class Application
    {
        public:
            Application(const WindowProps& props);
            ~Application()
            {
                glfwTerminate();
            }

            void Run();

        private:
            void ProcessInputs();

        private: 
            GLFWwindow* m_Window;
            bool m_Running { true };
    };
}