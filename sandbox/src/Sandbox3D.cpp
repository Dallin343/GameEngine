//
// Created by dallin on 9/11/20.
//

#include "Sandbox3D.h"
#include <Krispy/Materials/Material.h>

#include <imgui.h>

Sandbox3D::Sandbox3D()
: Layer("Sandbox3D"), m_CameraController({0.0f, 0.0f, 3.0f}, 45.0f, 1280.0f/720.0f, 0.1f, 100.0f) {

}

void Sandbox3D::OnAttach() {
    //m_WoodTexture = Krispy::Texture2D::Create("assets/textures/wall.jpg");
    //m_SmileyTexture = Krispy::Texture2D::Create("assets/textures/smiley.png");

    Krispy::Ref<Krispy::Texture2D> diffuse = Krispy::Texture2D::Create("assets/textures/box/diffuse.png");
    Krispy::Ref<Krispy::Texture2D> specular = Krispy::Texture2D::Create("assets/textures/box/specular.png");

    m_Shader = Krispy::Shader::Create("assets/shaders/LearnOpenGL.glsl");
    m_Material = Krispy::Material::Create(64.0f, diffuse, specular);
}

void Sandbox3D::OnDetach() {
    Layer::OnDetach();
}

void Sandbox3D::OnUpdate(Krispy::Timestep ts) {

    m_CameraController.OnUpdate(ts);

    Krispy::RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
    Krispy::RenderCommand::Clear();

    Krispy::Renderer::BeginScene(m_CameraController.GetCamera());

    static glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    for (auto & cubePosition : cubePositions) {
        Krispy::Renderer::DrawCube(m_Shader, {m_Material->GetDiffuseTexture(), m_Material->GetSpecularTexture()}, cubePosition);
    }

    Krispy::Renderer::EndScene();
}

void Sandbox3D::OnEvent(Krispy::Event &event) {
    m_CameraController.OnEvent(event);

}

void Sandbox3D::OnImGuiRender() {
    glm::vec3 pos = m_CameraController.GetCamera().GetPosition();
    glm::vec3 r = m_CameraController.GetCamera().Right;
    glm::vec3 u = m_CameraController.GetCamera().Up;
    glm::vec3 f = m_CameraController.GetCamera().Front;

    ImGui::Begin("Camera");
    ImGui::Text("Position: (%f, %f, %f)", pos.x, pos.y, pos.z);
    ImGui::Text("Rotation: Yaw = %f, Pitch = %f", m_CameraController.GetCamera().GetYaw(), m_CameraController.GetCamera().GetPitch());
    ImGui::Text("Rotation: Right Vector: <%f, %f, %f>", r.x, r.y, r.z);
    ImGui::Text("Rotation: Up Vector: <%f, %f, %f>", u.x, u.y, u.z);
    ImGui::Text("Rotation: Front Vector: <%f, %f, %f>", f.x, f.y, f.z);
    ImGui::End();
}

std::string Sandbox3D::ToString() const {
    return Layer::ToString();
}



