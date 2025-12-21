#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
}

void Camera::updateView(GLint uniform) {
    glUniformMatrix4fv(uniform, 1, GL_FALSE, &m_view[0][0]);
}

void Camera::setFov(double radians) {
    m_fov=std::fabs(radians);
}

void Camera::move(glm::vec3 position) {
    m_position=position;
    // Recalculate view matrix
    m_view=glm::lookAt(m_position, m_position+m_direction, m_up);
}

void Camera::look(glm::vec3 direction) {
    m_direction=glm::normalize(direction);
    // Recalculate view matrix
    m_view=glm::lookAt(m_position, m_position+m_direction, m_up);
}

void Camera::lookAt(glm::vec3 target) {
    m_direction=glm::normalize(target-m_position);
    // Recalculate view matrix
    m_view=glm::lookAt(m_position, target, m_up);
}

void Camera::pitch(double radians) {
}

void Camera::yaw(double radians) {
}
