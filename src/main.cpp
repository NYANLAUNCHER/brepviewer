#include <GL/glew.h>
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/io.hpp>
// STD
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
// local headers
#include "_generated/sys_paths.h"
#include "util.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "model.hpp"
#define FOV_INIT 45.0f
typedef unsigned int uint;

static uint gWINDOW_WIDTH=1600;
static uint gWINDOW_HEIGHT=1200;
static float gWINDOW_CENTER_X=(gWINDOW_WIDTH*0.5);
static float gWINDOW_CENTER_Y=(gWINDOW_HEIGHT*0.5);
static float gWINDOW_ASPECT=gWINDOW_WIDTH/gWINDOW_HEIGHT;
static double gScrollY=0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
    case GLFW_KEY_Q:// Kill the PROCESS!!!
        if (action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        break;
    case GLFW_KEY_ESCAPE:// Release the CURSOR!!!
        if (action == GLFW_RELEASE) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        break;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    gScrollY=yoffset;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    gWINDOW_WIDTH=width;
    gWINDOW_HEIGHT=height;
    gWINDOW_ASPECT=gWINDOW_WIDTH/gWINDOW_HEIGHT;
    glViewport(0, 0, gWINDOW_WIDTH, gWINDOW_HEIGHT);
}

void window_maximized_callback(GLFWwindow* window, int maximzied) {//{{{
    // Hides title bar when maximzied
    if (maximzied) {
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    } else {
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
    }
}//}}}

int main() {
    // Window & Context Setup: {{{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(gWINDOW_WIDTH, gWINDOW_HEIGHT, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }
    std::cout << CURSOR_HOME << CLR_AFTER;
    std::cout.flush();
    //}}}

    // GLFW Callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetWindowSizeCallback(window,framebuffer_size_callback);
    glfwSetWindowMaximizeCallback(window, window_maximized_callback);

    // Print Debug info
    std::cout << GREEN("SHADER_DIR = ") << BLUE(SHADER_DIR) << std::endl;
    std::cout << GREEN("TEXTURE_DIR = ") << BLUE(TEXTURE_DIR) << std::endl;

    float vertices[] = {
       //positions           //texture coords  //vertex normals
       // Face 1
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,       0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,       0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,       0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,       0.0f,  0.0f, -1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,       0.0f,  0.0f, -1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,       0.0f,  0.0f, -1.0f,
       // Face 2                                                  
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       0.0f,  0.0f, 1.0f, 
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,       0.0f,  0.0f, 1.0f, 
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,       0.0f,  0.0f, 1.0f, 
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,       0.0f,  0.0f, 1.0f, 
       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,       0.0f,  0.0f, 1.0f, 
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       0.0f,  0.0f, 1.0f, 
       // Face 3                                                  
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,      -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,      -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,      -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,      -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,      -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,      -1.0f,  0.0f,  0.0f,
       // Face 4                                                  
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,       1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       1.0f,  0.0f,  0.0f,
       // Face 5                                                  
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,       0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,       0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,       0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       0.0f, -1.0f,  0.0f,
       // Face 6                                                  
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,       0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,       0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,       0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,       0.0f,  1.0f,  0.0f 
    };
    // Setup Buffer Objects
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // VAO to handle vertex attributes
    glBindVertexArray(VAO);
    // VBO to store raw vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Create shader programs
    auto shdr_cube = Shader(SHADER_DIR"/lighting", "object");
    auto shdr_lightSrc = Shader(SHADER_DIR"/lighting", "source");
    // Initialize uniforms
    shdr_lightSrc.activate();
    shdr_lightSrc.setVec3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

    // Initialize transforms
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    // Create Camera
    Camera camera;
    camera.moveTo({0.0f, 5.0f, 0.0f});
    camera.lookAt({0.0f, 0.0f, 0.0f});

    double deltaTime=0;
    double accDelta=0;// accumulated delta for average frame rate
    double lastTime=0;
    uint d=0;
    std::pair cpos=util::getCursorPos();// for dynamic terminal output
    Mesh mesh(RESOURCE_DIR"/models/stanford_dragon/dragon.obj");
    glm::mat4 model1(1.0f);
    model1 = glm::rotate(model1, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    while (!glfwWindowShouldClose(window)) {
        // Setup
        double currTime = glfwGetTime();
        deltaTime = currTime - lastTime;
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.4f, 0.3f, 1.0f);
        // Handle Mouse Events {{{
        static double c_xpos=gWINDOW_CENTER_X, c_ypos=gWINDOW_CENTER_Y;
        static float pitch=0.0f, yaw=0.0f;
        if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            float lastX = c_xpos;
            float lastY = c_ypos;
            glfwGetCursorPos(window, &c_xpos, &c_ypos);
            float xoff = c_xpos - lastX;
            float yoff = lastY - c_ypos; // reversed, since glfw's y-coordinates range from bottom to top
            const float sensitivity = 0.025f;
            xoff *= sensitivity; yoff *= sensitivity;
            yaw += xoff;
            pitch += yoff;
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
            camera.look({
              cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
              -(sin(glm::radians(yaw)) * cos(glm::radians(pitch))),
              sin(glm::radians(pitch))
            });
        }
        static float fov=FOV_INIT;
        switch ((int)gScrollY) {
        case 1:
            fov -= 2.0f;
            gScrollY=0;
            break;
        case -1:
            fov += 2.0f;
            gScrollY=0;
            break;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS)
            fov=FOV_INIT;
        if (fov > 120.0f)
            fov=120.0f;
        if (fov < 10.0f)
            fov=10.0f;
        camera.m_fov=fov;
        //}}}
        // Handle Keyboard Events {{{
        float cameraSpeed = 3.0f * deltaTime; // adjust accordingly
        // Move Forward
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.forward(cameraSpeed);
        // Move Backward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.forward(-cameraSpeed);
        // Move Right
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.right(cameraSpeed);
        // Move Left
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.right(-cameraSpeed);
        //Move up
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.move(glm::vec3(0.0f, 0.0f, 1.0f)*cameraSpeed);
        // Move Down
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera.move(glm::vec3(0.0f, 0.0f, -1.0f)*cameraSpeed);
        //}}}

        // Pass view and proj matrices by reference
        camera.writeView(view);
        camera.writeProj(proj);

        // Draw light source
        shdr_lightSrc.activate();
        // Send MVP matrix to shader pipeline
        shdr_lightSrc.setMat4f("model", model);
        shdr_lightSrc.setMat4f("view", view);
        shdr_lightSrc.setMat4f("proj", proj);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /*
        // Draw cube
        shdr_cube.activate();
        // Send MVP matrix to shader pipeline
        glm::mat4 model1({
            { 0.5f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.5f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.5f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f },
        });
        shdr_cube.setMat4f("model", model1);
        shdr_cube.setMat4f("view", view);
        shdr_cube.setMat4f("proj", proj);
        glBindVertexArray(aiVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        */
        shdr_cube.activate();
        shdr_cube.setMat4f("model", model1);
        shdr_cube.setMat4f("view", view);
        shdr_cube.setMat4f("proj", proj);
        mesh.draw();

        // Print dynamic info
        accDelta += deltaTime;
        if (d >= 12) {// only print every 12 frames
            std::cout << CURSOR_POS(cpos.first, cpos.second) << CLR_AFTER;
            std::cout << "Delta Time: " << accDelta/d << "\n";
            std::cout << "Frame Rate: " << (int)(d/accDelta) << "\n";
            std::cout << "currTime: " << currTime << "\n";
            std::cout << "cursor: (" << c_xpos << ", " << c_ypos << ")\n";
            std::cout << "camera.getPos():" <<
                " X" << camera.getPos().x <<
                " Y" << camera.getPos().y <<
                " Z" << camera.getPos().z << "\n";
            std::cout << "camera.getUp():" <<
                " X" << camera.getUp().x <<
                " Y" << camera.getUp().y <<
                " Z" << camera.getUp().z << "\n";
            std::cout << "camera.getDirection():" <<
                " X" << camera.getDirection().x <<
                " Y" << camera.getDirection().y <<
                " Z" << camera.getDirection().z << "\n";
            std::cout << "Model Matrix (Light):" << model << "\n";
            std::cout << "Model Matrix (Object):" << model1 << "\n";
            std::cout << "View Matrix:" << camera.getView() << "\n";
            std::cout << "Projection Matrix:" << camera.getProj() << "\n";
            std::cout.flush();
            accDelta=0;
            d=0;
        };d++;

        // Reset
        glfwSwapBuffers(window);
        glfwPollEvents();
        lastTime = currTime;
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

