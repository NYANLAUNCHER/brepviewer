#include "camera.hpp"
#include "util.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
}

/*  Matrix Functions:  */

glm::mat4 Camera::getView() {
    m_view=glm::lookAt(m_position, m_position+m_direction, m_up);
    return m_view;
}

glm::mat4 Camera::getProj() {
    m_proj=glm::perspective(m_fov, m_aspect, m_near, m_far);
    return m_proj;
}

/*  Camera Controls:  */

// see: https://www.math3d.org/x6dcWlCwL5
void Camera::look(glm::vec3 direction) {
    //using util::coord::Spherical;
    //Spherical s(direction);
    //m_up = Spherical(s.r, s.theta, s.phi).toCartesian();
    m_direction = glm::normalize(direction);
}

void Camera::moveTo(glm::vec3 position) {
    m_position=position;
}

void Camera::move(glm::vec3 position) {
    m_position+=position;
}

void Camera::forward(float distance) {
    m_position+=getDirection()*distance;
}

void Camera::right(float distance) {
    m_position+=getRight()*distance;
}

void Camera::up(float distance) {
    m_position+=getUp()*distance;
}
