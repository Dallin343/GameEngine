//
// Created by dallin on 8/11/20.
//

#include "Application.h"

namespace Krispy {

    Application::Application() {
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application() {

    }

    void Application::Run() {
        while (m_Running) {
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
    }

    bool Application::OnWindowClose(WindowCloseEvent &event) {
        return false;
    }

    bool Application::OnWindowResize(WindowResizeEvent &event) {
        return false;
    }
}
