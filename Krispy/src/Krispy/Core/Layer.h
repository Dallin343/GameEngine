//
// Created by dallin on 8/13/20.
//

#pragma once

#include "Krispy/Events/Event.h"

namespace Krispy {
    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() {};

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() { return m_Name; }
    protected:
        std::string m_Name;
    };
}



