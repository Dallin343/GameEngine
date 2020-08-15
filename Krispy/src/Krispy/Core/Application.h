//
// Created by dallin on 8/11/20.
//
#pragma once

#include "Krispy/Window.h"

#include "Krispy/Events/Event.h"
#include "Krispy/Events/ApplicationEvent.h"
#include "Krispy/LayerStack.h"

namespace Krispy {
    class Application {
    public:
        Application();
        virtual ~Application();

        inline Application* Get() const { return s_Instance; }
        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
    private:
        bool OnWindowClose(WindowCloseEvent& event);
        bool OnWindowResize(WindowResizeEvent& event);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

        LayerStack m_LayerStack;

    private:
        Application* s_Instance;
    };

    //To be defined in client
    Application* CreateApplication();
}
