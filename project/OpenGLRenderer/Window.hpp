#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>
#include "Events/Event.hpp"


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
            inline void SetEventCallbackFn(std::function<void(Event&)> callback) { m_Data.eventCallback = callback; }

        private:
            std::function<void(Event&)> eventCallback {};
            GLFWwindow* m_Window;

            struct WindowData {
                std::string Title;
                int Width, Height;
                std::function<void(Event&)> eventCallback;
            };

            WindowData m_Data;
    };
}
