#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::setAspectRatio(const float aspectRatio) {
    m_aspectRatio = aspectRatio;
    m_projectionMatrixCache.first = true;
    m_viewProjectionMatrixCache.first = true;
}

void Camera::setPosition(const glm::vec3& position) {
    m_position = position;
    m_viewMatrixCache.first = true;
    m_viewProjectionMatrixCache.first = true;
}

void Camera::setYaw(const float yaw) {
    m_yaw = yaw;
    m_viewMatrixCache.first = true;
    m_viewProjectionMatrixCache.first = true;
}

void Camera::setPitch(const float pitch) {
    m_pitch = pitch;
    m_viewMatrixCache.first = true;
    m_viewProjectionMatrixCache.first = true;
}

void Camera::setRoll(const float roll) {
    m_roll = roll;
    m_viewMatrixCache.first = true;
    m_viewProjectionMatrixCache.first = true;
}

const glm::mat4& Camera::getView() const {
    auto& [isDirty, viewMatrix] { m_viewMatrixCache };
    if (!isDirty) {
        return viewMatrix;
    }

    glm::mat4 rotation{ 1.f };
    rotation = glm::rotate(rotation, glm::radians(m_yaw),   glm::vec3{ 0.f, 1.f, 0.f });
    rotation = glm::rotate(rotation, glm::radians(m_pitch), glm::vec3{ 1.f, 0.f, 0.f });
    rotation = glm::rotate(rotation, glm::radians(m_roll),  glm::vec3{ 0.f, 0.f, 1.f });

    const glm::vec3 forward{ glm::normalize(glm::vec3{ rotation * glm::vec4{ 0.f, 0.f, -1.f, 0.f } }) };
    const glm::vec3 up{ glm::normalize(glm::vec3{ rotation * glm::vec4{ 0.f, 1.f, 0.f, 0.f } }) };

    isDirty = false;
    viewMatrix = glm::lookAt(m_position, m_position + forward, up);
    return viewMatrix;
}

const glm::mat4& Camera::getProjection() const {
    auto& [isDirty, projectionMatrix] { m_projectionMatrixCache };
    if (!isDirty) {
        return projectionMatrix;
    }

    isDirty = false;
    projectionMatrix = glm::perspective(
        glm::radians(m_fov),
        m_aspectRatio,
        m_nearPlane,
        m_farPlane
    );
    return projectionMatrix;
}

const glm::mat4& Camera::getViewProjection() const {
    auto& [isDirty, viewProjectionMatrix] { m_viewProjectionMatrixCache };
    if (!isDirty) {
        return viewProjectionMatrix;
    }

    isDirty = false;
    viewProjectionMatrix = getProjection() * getView();
    return viewProjectionMatrix;
}
