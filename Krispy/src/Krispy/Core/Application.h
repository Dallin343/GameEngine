//
// Created by dallin on 8/11/20.
//
#pragma once


#include "Krispy/Core/Window.h"

#include "Krispy/Events/Event.h"
#include "Krispy/Events/ApplicationEvent.h"
#include "Krispy/ImGui/ImGuiLayer.h"
#include "Krispy/Core/LayerStack.h"

#include "Krispy/Renderer/Shader.h"
#include "Krispy/Renderer/Buffer.h"
#include "Krispy/Renderer/VertexArray.h"

namespace Krispy {
    class Application {
    public:
        Application();
        virtual ~Application();

        static Application& Get() { return *s_Instance; }

        inline Window& GetWindow() { return *m_Window; }

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        bool OnWindowClose(WindowCloseEvent& event);
        bool OnWindowResize(WindowResizeEvent& event);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;

        std::shared_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<Shader> m_Shader;
    private:
        static Application* s_Instance;
    };

    //To be defined in client
    Application* CreateApplication();
}
