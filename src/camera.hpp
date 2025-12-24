#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    // NOTE: only updated when getView() is ran
    glm::mat4 m_view=glm::mat4(1.0f);
    // NOTE: only updated when getProj() is ran
    glm::mat4 m_proj=glm::mat4(1.0f);
    // World Space Coordinates: (Assumes a right-hand coord system with Z pointing up)
    glm::vec3 m_position  = glm::vec3(0.0f, 0.0f, 0.0f);// init camera to be at world origin
    glm::vec3 m_right     = glm::vec3(1.0f, 0.0f, 0.0f);// positive X
    glm::vec3 m_direction = glm::vec3(0.0f,-1.0f, 0.0f);// negative Y
    glm::vec3 m_up        = glm::vec3(0.0f, 0.0f, 1.0f);// positive Z
    // Recalculate the view and projection matrices
    void update();
public:
    double m_width=1.0f;
    double m_height=1.0f;
    double m_near=0.01f;
    double m_far=100.0f;
    // Camera fov in radians
    double m_fov=glm::radians(45.0f);
    inline glm::vec3 getDirection() const {return glm::normalize(m_direction);}
    inline glm::vec3 getUp() const {return glm::normalize(m_up);}
    inline glm::vec3 getRight() const {return glm::normalize(m_right);}
    inline glm::vec3 getPos() const {return m_position;}
    // Constructor ty shi'
    Camera();
    
    /*  Matrix Functions:  */

    // Update then return the view matrix
    glm::mat4 getView();
    // Alias for `glm::mat4 view=getView();`
    inline void writeView(glm::mat4& view) {view=getView();}
    // Update then return the projection matrix
    glm::mat4 getProj();
    // Alias for `glm::mat4 proj=getProj();`
    inline void writeProj(glm::mat4& proj) {proj=getProj();}
    // Combination of getProj(glm::mat4& proj) and getView(glm::mat4& view)
    inline void writeVP(glm::mat4& view, glm::mat4& proj) {view=getView();proj=getProj();}
    // Pass view and projection directly to shader uniforms
    inline void writeVP(GLint u_view, GLint u_proj) {
        glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(m_view));
        glUniformMatrix4fv(u_proj, 1, GL_FALSE, glm::value_ptr(m_proj));
    }

    /*  Camera Controls:  */

    // Resize the camera viewport
    void resize(double width, double height);
    // Move camera to an absolute position in world space
    void move(glm::vec3 position);
    // The direction in which to point the camera
    void look(glm::vec3 direction);
    // Point the camera at a position in world space
    void lookAt(glm::vec3 target);
    // Move along m_direction vector by distance
    void forward(float distance);
    // Move along m_right vector by distance
    void right(float distance);
    // Move along m_up vector by distance
    void up(float distance);
};
