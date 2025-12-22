#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Camera {
private:
    glm::mat4 m_view=glm::mat4(1.0f);// init as identity matrix
    glm::vec3 m_position=glm::vec3(0.0f);// init camera to be at world origin
    glm::vec3 m_direction=glm::vec3(0.0f,0.0f,-1.0f);// init camera to point in negative Z
    glm::vec3 m_up=glm::vec3(0.0f, 1.0f, 0.0f);// init camera up direction to positive Y
    double m_fov=glm::radians(45.0f);
public:
    inline glm::mat4 getView() const {return m_view;}
    inline glm::vec3 getDirection() const {return m_direction;}
    inline glm::vec3 getUpVector() const {return m_up;}
    inline glm::vec3 getPos() const {return m_position;}
    // Write the view matrix to a uniform
    inline void update(GLint uniform) {
        glUniformMatrix4fv(uniform, 1, GL_FALSE, &m_view[0][0]);
    }
    // Write the view matrix to another variable
    inline void update(glm::mat4& view) {
        view=m_view;
    }
    Camera();
    // Set the fov to a value described in radians
    // Will use absolute value for negative inputs
    void setFov(double radians);
    // Move camera to a position in world space
    void move(glm::vec3 position);
    // The direction in which to point the camera
    void look(glm::vec3 direction);
    // Point the camera at a position in world space
    void lookAt(glm::vec3 target);
};
