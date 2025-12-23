#include "camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    m_proj=glm::perspective(glm::radians(m_fov), (m_width/m_height), m_near, m_far);
}

void Camera::resize(double width, double height) {
    m_width=width;
    m_height=height;
    calcView();
}

void Camera::write(glm::mat4& vp) {
    vp=m_proj*m_view;
}

void Camera::write(GLint uniform) {
    glm::mat4 m=m_proj*m_view;
    glUniformMatrix4fv(uniform, 1, GL_FALSE, &m[0][0]);
}

void Camera::move(glm::vec3 position) {
    m_position+=position;
    // Recalculate view matrix
    calcView();
}

void Camera::look(glm::vec3 direction) {
    m_direction=glm::normalize(direction);
    // Recalculate view matrix
    calcView();
}

void Camera::lookAt(glm::vec3 target) {
    m_direction=glm::normalize(target-m_position);
    // Recalculate view matrix
    calcView();
}

void Camera::forward(float distance) {
    m_position+=m_direction*distance;
    // Recalculate view matrix
    calcView();
}

void Camera::right(float distance) {
    m_position+=glm::cross(m_direction, m_up)*distance;
    // Recalculate view matrix
    calcView();
}

void Camera::up(float distance) {
    m_position+=m_up*distance;
    // Recalculate view matrix
    calcView();
}

