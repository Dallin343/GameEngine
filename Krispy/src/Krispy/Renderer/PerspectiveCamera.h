//
// Created by dallin on 8/24/20.
//

#pragma once

#include <glm/glm.hpp>

namespace Krispy {
    class PerspectiveCamera {
    public:
        PerspectiveCamera(
                const glm::vec3& position,
                float fov,
                float aspect,
                float near = 0.1f,
                float far = 100.0f);

        void SetProjection(float fov, float aspect, float near = 0.1f, float far = 100.0f);

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) {
            m_Position = position;
            Recalculate();
        }

        const float GetYaw() const { return m_Yaw; }
        const float GetPitch() const { return m_Pitch; }

        void Move(const glm::vec3& translation);
        void MoveTo(const glm::vec3& position);

        void Rotate(float yawDegrees, float pitchDegrees);
        void RotateTo(float yaw, float pitch);


        const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
        const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
        const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

        glm::vec3 Front = { 0.0f, 0.0f, -1.0f};
        glm::vec3 Up;
        glm::vec3 Right;
    private:
        void Recalculate();
    private:
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position;

        glm::vec3 m_WorldUp = {0.0f, 1.0f, 0.0f};

        float m_Yaw = -90.0f;
        float m_Pitch = 0.0f;

    };
}



