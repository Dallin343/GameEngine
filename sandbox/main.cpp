//
// Created by dallin on 8/11/20.
//

#include <Krispy.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer: public Krispy::Layer {
public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
        m_TriangleVA.reset(Krispy::VertexArray::Create());

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


        m_SquareVA.reset(Krispy::VertexArray::Create());

        float squareVertices[3 * 4] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f
        };

        std::shared_ptr<Krispy::VertexBuffer> squareVB;
        squareVB.reset(Krispy::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({
            {Krispy::ShaderDataType::Float3, "a_Position"}
        });

        m_SquareVA->AddVertexBuffer(squareVB);

        std::shared_ptr<Krispy::IndexBuffer> squareIB;
        unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        squareIB.reset(Krispy::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string redVertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main() {
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}
        )";

        std::string redFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            void main() {
                color = vec4(1.0, 0.4, 0.3, 1.0);
            }
        )";

        std::string blueVertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;
uniform mat4 u_Transform;

uniform mat4 u_ViewProjection;

void main() {
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}
        )";

        std::string blueFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            void main() {
                color = vec4(0.3, 4.0, 1.0, 1.0);
            }
        )";

        m_RedShader.reset(Krispy::Shader::Create(redVertexSrc, redFragmentSrc));
        m_BlueShader.reset(Krispy::Shader::Create(blueVertexSrc, blueFragmentSrc));
    }

    void OnUpdate(Krispy::Timestep ts) override {

        if (Krispy::Input::IsKeyPressed(KRISPY_KEY_RIGHT)) {
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        }
        if (Krispy::Input::IsKeyPressed(KRISPY_KEY_LEFT)) {
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        }

        if (Krispy::Input::IsKeyPressed(KRISPY_KEY_UP)) {
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        }
        if (Krispy::Input::IsKeyPressed(KRISPY_KEY_DOWN)) {
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        }

        if (Krispy::Input::IsKeyPressed(KRISPY_KEY_A)) {
            m_CameraRotation += m_CameraRotationSpeed * ts;
        }
        if (Krispy::Input::IsKeyPressed(KRISPY_KEY_D)) {
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        }

        Krispy::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
        Krispy::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Krispy::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                glm::vec3 pos( y * 0.11f, x * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Krispy::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
            }

        }

        Krispy::Renderer::Submit(m_RedShader, m_TriangleVA);

        Krispy::Renderer::EndScene();
    }

    void OnEvent(Krispy::Event &event) override {

    }

private:
    Krispy::Ref<Krispy::VertexArray> m_TriangleVA;
    Krispy::Ref<Krispy::VertexArray> m_SquareVA;
    Krispy::Ref<Krispy::Shader> m_RedShader;
    Krispy::Ref<Krispy::Shader> m_BlueShader;
    Krispy::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
    float m_CameraRotation = 0.0f;
    float m_CameraMoveSpeed = 1.0f;
    float m_CameraRotationSpeed = 180.0f;
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