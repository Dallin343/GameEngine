//
// Created by dallin on 8/15/20.
//

#pragma once

#include "Krispy/Core/Layer.h"

#include "Krispy/Events/ApplicationEvent.h"
#include "Krispy/Events/MouseEvent.h"
#include "Krispy/Events/KeyEvent.h"

namespace Krispy {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer() : Layer("ImGuiLayer") {};
        ~ImGuiLayer() = default;

        void OnAttach() override;

        void OnDetach() override;

        void OnEvent(Event& event);

        void OnUpdate() override;

        void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_Time;
    };
}



