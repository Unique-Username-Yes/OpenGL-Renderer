#pragma once
#include "Events/Event.hpp"
#include <string>

namespace OpenGLRenderer
{
    class Layer
    {
        public:
            Layer(const std::string& layerName = "Layer");
            virtual ~Layer();

            virtual void OnAttach() {}
            virtual void OnUpdate(float timestep) {}
            virtual void OnDetach() {}
            virtual void OnEvent(Event &event) {}

            virtual const std::string& GetName() const { return m_DebugName; }

        protected:
            std::string m_DebugName {};
    };
}
