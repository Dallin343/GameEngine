//
// Created by dallin on 8/24/20.
//

#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Krispy {
    PerspectiveCamera::PerspectiveCamera(
            const glm::vec3& position,
            float fov,
            float aspect,
            float near,
            float far)
            : m_ProjectionMatrix(glm::perspective(fov, aspect, near, far)), m_ViewMatrix(1.0f), m_Position(position) {

        Recalculate();
    }

    void PerspectiveCamera::SetProjection(float fov, float aspect, float near, float far) {
        m_ProjectionMatrix = glm::perspective(fov, aspect, near, far);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void PerspectiveCamera::Recalculate() {
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, m_WorldUp));
        Up = glm::normalize(glm::cross(Right, m_WorldUp));

        m_ViewMatrix = glm::lookAt(m_Position, m_Position + Front, m_WorldUp);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }


    void PerspectiveCamera::Move(const glm::vec3 &translation) {
        m_Position += translation;

        Recalculate();
    }

    void PerspectiveCamera::MoveTo(const glm::vec3 &position) {
        m_Position = position;

        Recalculate();
    }

    void PerspectiveCamera::Rotate(float yawDegrees, float pitchDegrees) {
        m_Yaw += yawDegrees;
        m_Pitch += pitchDegrees;

        Recalculate();
    }

    void PerspectiveCamera::RotateTo(float yaw, float pitch) {
        m_Yaw = yaw;
        m_Pitch = pitch;

        Recalculate();
    }
}

