//
// Created by dallin on 8/13/20.
//

#pragma once

#include "Krispy/Events/Event.h"
#include "Timestep.h"

namespace Krispy {
    class Layer: public Debuggable {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() {};

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnEvent(Event& event) {}
        virtual void OnImGuiRender() {}

        inline const std::string& GetName() const { return m_Name; }

        std::string ToString() const override { return GetName(); };

    protected:
        std::string m_Name;
    };
}



