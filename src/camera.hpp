#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    // NOTE: only updated when getView() is ran
    glm::mat4 m_view = glm::mat4(1.0f);
    // NOTE: only updated when getProj() is ran
    glm::mat4 m_proj = glm::mat4(1.0f);
    // World Space Coordinates: (Assumes a right-hand coord system with Z pointing up)
    glm::vec3 m_position  = glm::vec3(0.0f, 0.0f, 0.0f);// init camera to be at world origin
    glm::vec3 m_right     = glm::vec3(1.0f, 0.0f, 0.0f);// positive X
    glm::vec3 m_direction = glm::vec3(0.0f,-1.0f, 0.0f);// negative Y
    glm::vec3 m_up        = glm::vec3(0.0f, 0.0f, 1.0f);// positive Z
public:
    double m_aspect = 1.0f;
    double m_near = 0.01f;
    double m_far = 100.0f;
    double m_fov = glm::radians(45.0f);
    // Constructor ty shi'
    Camera();
    
    inline glm::vec3 getDirection() const {return glm::normalize(m_direction);}
    inline glm::vec3 getUp() const {return glm::normalize(m_up);}
    inline glm::vec3 getRight() const {return glm::normalize(m_right);}
    inline glm::vec3 getPos() const {return m_position;}
    
    // Recalculate m_view before returning it
    glm::mat4 getView();
    // Directly write m_view to a variable
    inline void writeView(glm::mat4& view) {view=getView();}
    // Recalculate m_proj before returning it
    glm::mat4 getProj();
    // Directly write m_proj to a variable
    inline void writeProj(glm::mat4& proj) {proj=getProj();}
    // Return the combined View and Projection matrix
    inline glm::mat4 getVP() {return getProj() * getView();}
    // Directly write m_proj to an external variable
    inline void writeVP(glm::mat4& vp) {vp=getVP();}

    // Move camera to an absolute position in world space
    void moveTo(glm::vec3 position);
    // Move camera to a relative position in world space
    void move(glm::vec3 position);
    // The direction in which to point the camera
    void look(glm::vec3 direction);
    // Point the camera at a coordinate in world space
    void lookAt(glm::vec3 direction);
    // Move along m_direction vector by distance
    void forward(float distance);
    // Move along m_right vector by distance
    void right(float distance);
    // Move along m_up vector by distance
    void up(float distance);
};
