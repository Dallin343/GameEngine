//
// Created by dallin on 9/11/20.
//

#pragma once
#include <Krispy.h>
#include <Krispy/Core/PerspectiveCameraController.h>

class Sandbox3D : public Krispy::Layer {
public:
    Sandbox3D();

    virtual ~Sandbox3D() = default;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(Krispy::Timestep ts) override;
    void OnEvent(Krispy::Event &event) override;
    void OnImGuiRender() override;

    std::string ToString() const override;

private:
    Krispy::Ref<Krispy::Texture2D> m_WoodTexture;
    Krispy::Ref<Krispy::Texture2D> m_SmileyTexture;

    Krispy::Ref<Krispy::Model> m_Model;
    Krispy::Ref<Krispy::Shader> m_Shader;
    Krispy::PerspectiveCameraController m_CameraController;
    Krispy::Ref<Krispy::Material> m_Material;

    //Krispy::OrthographicCameraController m_CameraController;

};

