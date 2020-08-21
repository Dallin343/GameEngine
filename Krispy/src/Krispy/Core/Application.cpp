//
// Created by dallin on 8/11/20.
//

#include "Application.h"

#include "Krispy/Renderer/Buffer.h"

#include "Krispy/Renderer/Renderer.h"

namespace Krispy {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[3 * 3] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };

        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
                {ShaderDataType::Float3, "a_Position"}
        };

        m_VertexBuffer->SetLayout(layout);

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        unsigned int indices[3] = { 0, 1, 2 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;

void main() {
    gl_Position = vec4(a_Position, 1.0);
}
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            void main() {
                color = vec4(1.0, 0.0, 0.0, 1.0);
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    Application::~Application() {

    }

    void Application::Run() {
        while (m_Running) {
            RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
            RenderCommand::Clear();

            Renderer::BeginScene();

            m_Shader->Bind();
            Renderer::Submit(m_VertexArray);
            Renderer::EndScene();

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

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
        return false;
    }
}
