//
// Created by dallin on 9/11/20.
//

#pragma once
#include "Krispy/Renderer/PerspectiveCamera.h"
#include "Krispy/Core/Timestep.h"

#include "Krispy/Events/ApplicationEvent.h"
#include "Krispy/Events/MouseEvent.h"

namespace Krispy {
    class PerspectiveCameraController {

    public:
        PerspectiveCameraController(
                const glm::vec3& position = { 0.0f, 0.0f, 0.0f},
                float fov = 45.0f,
                float aspect = 1280.f / 720.f,
                float near = 0.1f,
                float far = 100.0f);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        PerspectiveCamera& GetCamera() { return m_Camera; }
        const PerspectiveCamera& GetCamera() const { return m_Camera; }

        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }

    private:
        bool OnMouseMoved(MouseMovedEvent& e);
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    private:
        float m_FOV;
        float m_AspectRatio;
        float m_Near, m_Far;
        float m_ZoomLevel = 1.0f;
        PerspectiveCamera m_Camera;

        bool m_Rotation;
        glm::vec3 m_CameraPosition;
        glm::vec3 m_CameraFront;
        glm::vec3 m_CameraUp;
        glm::vec3 m_CameraRight;
        glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f};
        float m_Yaw = -90.0f, m_Pitch = 0.0f;

        float m_LastX = 640, m_LastY = 360;

        float m_CameraBaseTranslationSpeed = 5.0f;
        float m_CameraTranslationSpeed = 50.0f, m_CameraRotationSpeed = 180.0f;

    };
}






