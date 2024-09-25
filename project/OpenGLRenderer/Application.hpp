#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include "LayerStack.hpp"
#include "Window.hpp"

namespace OpenGLRenderer 
{
    class Application
    {
        public:
            Application(const WindowProps& props);
            ~Application() {}

            void Run();

            inline void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

        private: 
            Window* m_Window;
            bool m_Running { true };
            LayerStack m_LayerStack {};
    };
}