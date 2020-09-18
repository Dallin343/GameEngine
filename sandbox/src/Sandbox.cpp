//
// Created by dallin on 8/11/20.
//

#include <Krispy.h>
#include <Krispy/Core/Entry.h>

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"
#include "Sandbox3D.h"

class ExampleLayer: public Krispy::Layer {
public:
    ExampleLayer() : Layer("Example"), m_CameraController(1280.f / 720.f, true) {

        m_SquareVA = Krispy::VertexArray::Create();

        float squareVertices[5 * 4] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };

        std::shared_ptr<Krispy::VertexBuffer> squareVB;
        squareVB = Krispy::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

        squareVB->SetLayout({
            {Krispy::ShaderDataType::Float3, "a_Position"},
            { Krispy::ShaderDataType::Float2, "a_TexCoord"}
        });

        m_SquareVA->AddVertexBuffer(squareVB);

        std::shared_ptr<Krispy::IndexBuffer> squareIB;
        unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        squareIB = Krispy::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        m_SquareVA->SetIndexBuffer(squareIB);


        m_FlatColorShader = Krispy::Shader::Create("assets/shaders/FlatColor.glsl");
        m_TextureShader = Krispy::Shader::Create("assets/shaders/Texture.glsl");
        m_ChernoTexture = Krispy::Texture2D::Create("assets/textures/ChernoLogo.png");
        m_Texture = Krispy::Texture2D::Create("assets/textures/Checkerboard.png");

        m_TextureShader->Bind();
        m_TextureShader->SetInt("u_Texture", 0);
    }

    void OnUpdate(Krispy::Timestep ts) override {

        m_CameraController.OnUpdate(ts);

        Krispy::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
        Krispy::RenderCommand::Clear();

        //Krispy::Renderer::BeginScene(m_CameraController.GetCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        m_FlatColorShader->Bind();
        m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                glm::vec3 pos( y * 0.11f, x * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Krispy::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }

        }

        m_Texture->Bind();
        Krispy::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_ChernoTexture->Bind();
        Krispy::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        // Triangle
        //Krispy::Renderer::Submit(m_TriangleShader, m_TriangleVA);

        Krispy::Renderer::EndScene();
    }

    void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Krispy::Event &event) override {
        m_CameraController.OnEvent(event);
    }

private:
    Krispy::Ref<Krispy::VertexArray> m_SquareVA;
    Krispy::Ref<Krispy::Shader> m_FlatColorShader, m_TextureShader;
    Krispy::Ref<Krispy::Texture2D> m_Texture, m_ChernoTexture;


    Krispy::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = {0.0f, 0.5f, 0.5f};
};

class Sandbox : public Krispy::Application {
public:
    Sandbox() {
        //PushLayer(new ExampleLayer());
        PushLayer(new Sandbox3D());
    }

    ~Sandbox() {

    }
};

Krispy::Application* Krispy::CreateApplication() {
    Sandbox* sandbox = new Sandbox();
    return sandbox;
};