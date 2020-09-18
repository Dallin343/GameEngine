//
// Created by dallin on 9/11/20.
//

#include "Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D") , m_CameraController(1280.f / 720.f) {
    m_Texture = Krispy::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnAttach() {
}

void Sandbox2D::OnDetach() {
    Layer::OnDetach();
}

void Sandbox2D::OnUpdate(Krispy::Timestep ts) {

    m_CameraController.OnUpdate(ts);

    Krispy::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
    Krispy::RenderCommand::Clear();

    Krispy::Renderer2D::BeginScene(m_CameraController.GetCamera());

    for (float y = -50.0f; y < 50.0f; y += 0.5f) {
        for (float x = -50.0f; x < 50.0f; x += 0.5f) {
            Krispy::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, m_Texture);
        }
    }

//    Krispy::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.0f, 1.0f});
//    Krispy::Renderer2D::DrawQuad({-0.5f, 0.5f, 0.1f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.7f, 0.7f});
//    Krispy::Renderer2D::DrawQuad({0.5f, 0.5f, -0.1f}, {10.0f, 10.0f}, m_Texture);
    Krispy::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Krispy::Event &event) {
    m_CameraController.OnEvent(event);

}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

std::string Sandbox2D::ToString() const {
    return Layer::ToString();
}
