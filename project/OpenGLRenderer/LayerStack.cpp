#include <algorithm>
#include "LayerStack.hpp"

namespace OpenGLRenderer
{
    LayerStack::LayerStack()
    {

    }

    LayerStack::~LayerStack()
    {
        for(Layer* layer: m_Layers)
        {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_Layers.emplace_back(layer);
        layer->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if(it != m_Layers.end())
        {
            m_Layers.erase(it);
        }
        layer->OnDetach();
    }
}