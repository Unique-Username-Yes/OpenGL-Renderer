#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>
#include <memory>
#include "Events/Event.hpp"
#include <iostream>


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
            ~Window(){ }

            void OnUpdate();
            inline float GetTime() const { return static_cast<float>(glfwGetTime()); }
            inline void SetEventCallbackFn(std::function<void(Event&)> callback) { m_Data.m_EventCallback = callback; }

        private:
            static void GLFWwindowDeleter(GLFWwindow* window)
            {
                if(window)
                    glfwDestroyWindow(window);
            }

        private:
            using unique_glfwwindow_ptr = std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>>;

            unique_glfwwindow_ptr m_Window;

            std::function<void(Event&)> m_EventCallback {};

            struct WindowData {
                std::string Title;
                int Width, Height;
                std::function<void(Event&)> m_EventCallback;
            };

            WindowData m_Data {};
    };
}
