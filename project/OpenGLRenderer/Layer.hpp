#pragma once

namespace OpenGLRenderer
{
    class Layer
    {
        public:
            Layer();
            virtual ~Layer();

            virtual void OnAttach() {}
            virtual void OnUpdate(float timestep) {}
            virtual void OnDetach() {}
    };
}
