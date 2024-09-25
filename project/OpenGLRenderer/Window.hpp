#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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

    class Window
    {
        public:
            Window(const WindowProps& props = WindowProps{});
            inline ~Window(){ glfwTerminate(); }

            void OnUpdate();
            inline float GetTime() const { return static_cast<float>(glfwGetTime()); }

            inline bool IsCloseEventTriggered() const { return glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS; }

        private:
            GLFWwindow* m_Window;
    };
}
