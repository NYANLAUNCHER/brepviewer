#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::mat4 m_view=glm::mat4(1.0f);
    glm::mat4 m_proj=glm::mat4(1.0f);
    glm::vec3 m_position=glm::vec3(0.0f);// init camera to be at world origin
    glm::vec3 m_direction=glm::vec3(0.0f,0.0f,-1.0f);// init camera to point in negative Z
    glm::vec3 m_up=glm::vec3(0.0f, 1.0f, 0.0f);// init camera up direction to positive Y
    inline void calcView() {
        m_view=glm::lookAt(m_position, m_position+m_direction, m_up);
    }
public:
    double m_width=1.0f;
    double m_height=1.0f;
    double m_far=100.0f;
    double m_near=0.01f;
    double m_fov=glm::radians(45.0f);
    // Return the view matrix
    inline glm::mat4 getView() const {return m_view;}
    inline glm::mat4 getProj() const {return m_proj;}
    inline glm::vec3 getDirection() const {return m_direction;}
    inline glm::vec3 getUp() const {return m_up;}
    inline glm::vec3 getPos() const {return m_position;}
    // Write the combined view & projection matrix
    void write(glm::mat4& vp);
    // Write the combined view & projection matrix
    void write(GLint uniform);
    Camera();
    void resize(double width, double height);
    // Move camera to an absolute position in world space
    void move(glm::vec3 position);
    // The direction in which to point the camera
    void look(glm::vec3 direction);
    // Point the camera at a position in world space
    void lookAt(glm::vec3 target);
    // Move along m_direction vector by distance
    void forward(float distance);
    // Move along the right vector of the camera by distance
    void right(float distance);
    // Move along m_up vector by distance
    void up(float distance);
};
