//
// Created by dallin on 9/11/20.
//

#include "PerspectiveCameraController.h"

namespace Krispy {
    PerspectiveCameraController::PerspectiveCameraController(const glm::vec3& position, float fov,
                                                             float aspect, float near, float far)
            :  m_FOV(fov), m_Near(near), m_Far(far), m_AspectRatio(aspect),
            m_CameraPosition(position), m_Camera(position, glm::radians(m_FOV), aspect, m_Near, m_Far) {

    }

    void PerspectiveCameraController::OnUpdate(Timestep ts) {
        if (Input::IsKeyPressed(KRISPY_KEY_W)) {
            m_CameraPosition += m_Camera.Front * m_CameraTranslationSpeed * (float)ts;
        } if (Input::IsKeyPressed(KRISPY_KEY_S)) {
            m_CameraPosition -= m_Camera.Front * m_CameraTranslationSpeed * (float)ts;
        }

        if (Input::IsKeyPressed(KRISPY_KEY_D)) {
            m_CameraPosition += m_Camera.Right * m_CameraTranslationSpeed * (float)ts;
        } if (Input::IsKeyPressed(KRISPY_KEY_A)) {
            m_CameraPosition -= m_Camera.Right * m_CameraTranslationSpeed * (float)ts;
        }

        m_Camera.MoveTo(m_CameraPosition);

        m_CameraTranslationSpeed = m_CameraBaseTranslationSpeed * m_ZoomLevel;
    }

    void PerspectiveCameraController::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResized));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMoved));
    }

    bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent &e) {
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::min(std::max(m_ZoomLevel, 0.25f), 2.0f);
        m_Camera.SetProjection(glm::radians(m_FOV * m_ZoomLevel), m_AspectRatio, m_Near, m_Far);
        return false;
    }

    bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent &e) {
        m_AspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
        m_Camera.SetProjection(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far);
        return false;
    }

    bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent &e) {
        const float sens = 0.1f;
        float xOff = e.GetX() - m_LastX;
        float yOff = m_LastY - e.GetY();
        m_LastX = e.GetX();
        m_LastY = e.GetY();

        m_Yaw += xOff * sens;
        m_Pitch += yOff * sens;

        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        m_Camera.RotateTo(m_Yaw, m_Pitch);

        return false;
    }
}

