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
    // Clamps m_fov between two degrees expressed in radians
    // Limit order doesnt matter
    std::pair<double,double> m_fovLimit={glm::radians(10.0f), glm::radians(120.0f)};
    inline glm::mat4 getView() const {return m_view;}
    inline glm::vec3 getDirection() const {return m_direction;}
    inline glm::vec3 getUpVector() const {return m_up;}
    inline glm::vec3 getPos() const {return m_position;}
    Camera();
    // Write the view matrix to a uniform
    void updateView(GLint uniform);
    // Write the view matrix to another variable
    void updateView(glm::mat4& view);
    // Set the fov to a value described in radians
    // Will use absolute value for negative inputs
    void setFov(double radians);
    // Move camera to a position in world space
    void move(glm::vec3 position);
    // The direction in which to point the camera
    void look(glm::vec3 direction);
    // Point the camera at a position in world space
    void lookAt(glm::vec3 target);
    // Rotate camera based on pitch angle expressed in radians
    void pitch(double radians);
    // Rotate camera based on yaw angle expressed in radians
    void yaw(double radians);
    // Rotate camera based on yaw angle expressed in radians
    void roll(double radians);
};
