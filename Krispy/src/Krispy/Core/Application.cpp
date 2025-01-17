//
// Created by dallin on 8/11/20.
//

#include "Application.h"

#include "Krispy/Renderer/Buffer.h"

#include "Krispy/Renderer/Renderer.h"
#include "Timestep.h"

//Temporary
#include <GLFW/glfw3.h>

namespace Krispy {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        KRISPY_PROFILE_FUNCTION();

        s_Instance = this;

        m_Window = Scope<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {

    }

    void Application::Run() {
        while (m_Running) {
            float time = (float)glfwGetTime();
            Timestep ts = time - m_LastFrameTime;
            m_LastFrameTime = time;

            {
                KRISPY_PROFILE_SCOPE("Layer OnUpdate");
                if (!m_Minimized) {
                    for (Layer* layer : m_LayerStack) {
                        layer->OnUpdate(ts);
                    }
                }
            }

            {
                KRISPY_PROFILE_SCOPE("ImGuiLayer OnUpdate");
                m_ImGuiLayer->Begin();
                for (Layer* layer : m_LayerStack) {
                    layer->OnImGuiRender();
                }
                m_ImGuiLayer->End();
            }



            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

        // Iterate through layers, starting at the front, and going to the back
        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend();) {
            if (event.Handled) {
                break;
            }
            (*it++)->OnEvent(event);
        }
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *overlay) {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();

    }

    bool Application::OnWindowClose(WindowCloseEvent &event) {
        m_Running = false;
        return KRISPY_EVENT_HANDLED;
    }

    bool Application::OnWindowResize(WindowResizeEvent &event) {
        KRISPY_CORE_INFO("{0}, {1}", event.GetWidth(), event.GetHeight());
        if (event.GetWidth() == 0 || event.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

        return false;
    }
}
