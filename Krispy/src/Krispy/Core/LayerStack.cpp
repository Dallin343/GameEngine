//
// Created by dallin on 8/13/20.
//

#include "LayerStack.h"

namespace Krispy {
    LayerStack::LayerStack() {
    }

    LayerStack::~LayerStack() {
        for (Layer *layer : m_Layers) {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer *layer) {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsert, layer);
        m_LayerInsert++;
    }

    void LayerStack::PushOverlay(Layer *overlay) {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer *layer) {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsert, layer);

        if (it != m_Layers.end()) {
            layer->OnDetach();
            m_Layers.erase(it);
            m_LayerInsert--;
        }
    }

    void LayerStack::PopOverlay(Layer *overlay) {
        auto it = std::find(m_Layers.begin() + m_LayerInsert, m_Layers.end(), overlay);

        if (it != m_Layers.end()) {
            overlay->OnDetach();
            m_Layers.erase(it);
        }
    }

    std::string LayerStack::ToString() const {
        std::stringstream ss;
        ss << "LayerStack: " << m_Layers.size() << " layers in stack." << std::endl;
        for (Layer *layer : m_Layers) {
            ss << "-- Layer: " << layer->ToString() << std::endl;
        }
        return ss.str();
    };
}



