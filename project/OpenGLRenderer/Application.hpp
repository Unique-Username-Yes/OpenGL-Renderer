#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include "LayerStack.hpp"
#include "Window.hpp"
#include "Events/Event.hpp"
#include <memory>

namespace OpenGLRenderer 
{
    class Application
    {
        public:
            Application(const WindowProps& props);
            ~Application() {}

            void Run();
            void OnEvent(Event &event);

            inline void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

        private: 
            std::unique_ptr<Window> m_Window;
            bool m_Running { true };
            LayerStack m_LayerStack {};
    };
}