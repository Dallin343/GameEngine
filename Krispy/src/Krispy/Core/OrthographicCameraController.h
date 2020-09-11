//
// Created by dallin on 9/11/20.
//

#pragma once
#include "Krispy/Renderer/OrthographicCamera.h"
#include "Krispy/Core/Timestep.h"

#include "Krispy/Events/ApplicationEvent.h"
#include "Krispy/Events/MouseEvent.h"

namespace Krispy {
    class OrthographicCameraController {

    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;
        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 10.0f, m_CameraRotationSpeed = 180.f;

    };
}



