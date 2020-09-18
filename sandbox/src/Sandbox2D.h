//
// Created by dallin on 9/11/20.
//

#pragma once
#include <Krispy.h>

class Sandbox2D : public Krispy::Layer {
public:
    Sandbox2D();

    virtual ~Sandbox2D() = default;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(Krispy::Timestep ts) override;
    void OnEvent(Krispy::Event &event) override;
    void OnImGuiRender() override;

    std::string ToString() const override;

private:
    Krispy::Ref<Krispy::Shader> m_FlatColorShader;
    Krispy::Ref<Krispy::VertexArray> m_SquareVA;
    glm::vec4 m_SquareColor = {0.0f, 0.5f, 0.5f, 1.0f};

    Krispy::Ref<Krispy::Texture2D> m_Texture;

    Krispy::OrthographicCameraController m_CameraController;

};


