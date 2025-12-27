#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    Camera() = default;

    explicit Camera(const glm::vec3& position) {
        setPosition(position);
    }

    void setAspectRatio(const float aspectRatio);
    void setPosition(const glm::vec3& position);
    void setYaw(const float yaw);
    void setPitch(const float pitch);
    void setRoll(const float roll);

    [[nodiscard]] glm::vec3 getPosition() const { return m_position; }
    [[nodiscard]] float getYaw() const { return m_yaw; }
    [[nodiscard]] float getPitch() const { return m_pitch; }
    [[nodiscard]] float getRoll() const { return m_roll; }
    [[nodiscard]] float getAspectRatio() const { return m_aspectRatio; }

    const glm::mat4& getView() const;
    const glm::mat4& getProjection() const;
    const glm::mat4& getViewProjection() const;

private:
    glm::vec3 m_position{};
    float m_yaw{};
    float m_pitch{};
    float m_roll{};

    float m_aspectRatio{};
    float m_fov{ 60.f };
    float m_nearPlane{ 0.1f };
    float m_farPlane{ 500.f };

    mutable std::pair<bool, glm::mat4> m_viewMatrixCache{};
    mutable std::pair<bool, glm::mat4> m_projectionMatrixCache{};
    mutable std::pair<bool, glm::mat4> m_viewProjectionMatrixCache{};
};

#endif // CAMERA_H
