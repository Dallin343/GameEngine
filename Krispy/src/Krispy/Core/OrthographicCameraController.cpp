//
// Created by dallin on 9/11/20.
//

#include "OrthographicCameraController.h"

namespace Krispy {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    :   m_Rotation(rotation), m_AspectRatio(aspectRatio),
        m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel) {


    }

    void OrthographicCameraController::OnUpdate(Timestep ts) {
        if (Input::IsKeyPressed(KRISPY_KEY_D)) {
            m_CameraPosition.x += m_CameraTranslationSpeed * ts;
        } if (Input::IsKeyPressed(KRISPY_KEY_A)) {
            m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        }

        if (Input::IsKeyPressed(KRISPY_KEY_W)) {
            m_CameraPosition.y += m_CameraTranslationSpeed * ts;
        } if (Input::IsKeyPressed(KRISPY_KEY_S)) {
            m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
        }

        if (Input::IsKeyPressed(KRISPY_KEY_Q)) {
            m_CameraRotation += m_CameraRotationSpeed * ts;
        } if (Input::IsKeyPressed(KRISPY_KEY_E)) {
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        }
    }

    void OrthographicCameraController::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e) {
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e) {
        return false;
    }
}

