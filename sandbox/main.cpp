//
// Created by dallin on 8/11/20.
//

#include <Krispy.h>

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer: public Krispy::Layer {
public:
    ExampleLayer() : Layer("Example"), m_CameraController(1280.f / 720.f, true) {
        m_TriangleVA = Krispy::VertexArray::Create();

        float triangleVertices[3 * 3] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };

        std::shared_ptr<Krispy::VertexBuffer> triangleVB;
        triangleVB.reset(Krispy::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));

        triangleVB->SetLayout({
            {Krispy::ShaderDataType::Float3, "a_Position"}
        });

        m_TriangleVA->AddVertexBuffer(triangleVB);

        std::shared_ptr<Krispy::IndexBuffer> triangleIB;
        unsigned int triangleIndices[3] = {0, 1, 2 };
        triangleIB.reset(Krispy::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
        m_TriangleVA->SetIndexBuffer(triangleIB);


        m_SquareVA = Krispy::VertexArray::Create();

        float squareVertices[5 * 4] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };

        std::shared_ptr<Krispy::VertexBuffer> squareVB;
        squareVB.reset(Krispy::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({
            {Krispy::ShaderDataType::Float3, "a_Position"},
            { Krispy::ShaderDataType::Float2, "a_TexCoord"}
        });

        m_SquareVA->AddVertexBuffer(squareVB);

        std::shared_ptr<Krispy::IndexBuffer> squareIB;
        unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        squareIB.reset(Krispy::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string triangleVertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main() {
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}
        )";

        std::string triangleFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            void main() {
                color = vec4(1.0, 0.4, 0.3, 1.0);
            }
        )";

        std::string squareVertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;
uniform mat4 u_Transform;

uniform mat4 u_ViewProjection;

void main() {
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}
        )";

        std::string squareFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            uniform vec3 u_Color;

            void main() {
                color = vec4(u_Color, 1.0);
            }
        )";

        m_TriangleShader = Krispy::Shader::Create("TriangleShader", triangleVertexSrc, triangleFragmentSrc);
        m_FlatColorShader = Krispy::Shader::Create("FlatColorShader", squareVertexSrc, squareFragmentSrc);
        m_TextureShader = Krispy::Shader::Create("assets/shaders/Texture.glsl");
        m_ChernoTexture = Krispy::Texture2D::Create("assets/textures/ChernoLogo.png");
        m_Texture = Krispy::Texture2D::Create("assets/textures/Checkerboard.png");

        m_TextureShader->Bind();
        m_TextureShader->UploadUniformUInt("u_Texture", 0);
    }

    void OnUpdate(Krispy::Timestep ts) override {

        m_CameraController.OnUpdate(ts);

        Krispy::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
        Krispy::RenderCommand::Clear();

        Krispy::Renderer::BeginScene(m_CameraController.GetCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        m_FlatColorShader->Bind();
        m_FlatColorShader->UploadUniformFloat3("u_Color", m_SquareColor);

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
    Krispy::Ref<Krispy::VertexArray> m_TriangleVA;
    Krispy::Ref<Krispy::Shader> m_TriangleShader;

    Krispy::Ref<Krispy::VertexArray> m_SquareVA;
    Krispy::Ref<Krispy::Shader> m_FlatColorShader, m_TextureShader;
    Krispy::Ref<Krispy::Texture2D> m_Texture, m_ChernoTexture;


    Krispy::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = {0.0f, 0.5f, 0.5f};
};

class Sandbox : public Krispy::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {

    }
};

Krispy::Application* Krispy::CreateApplication() {
    Sandbox* sandbox = new Sandbox();
    return sandbox;
};