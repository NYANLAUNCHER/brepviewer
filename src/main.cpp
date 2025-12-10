#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <chrono>
#include <thread>
// local headers
#include "_generated/sys_paths.h"
#include "shader.hpp"
#include "texture.hpp"
#include "util.hpp"
#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 1200
#define WINDOW_CENTER_X 600
#define WINDOW_CENTER_Y 600
typedef unsigned int uint;

static float PITCH=0.0f;
static float YAW=-90.0f;
//static float ROLL=0;
static glm::vec3 direction;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    float lastX=WINDOW_CENTER_X, lastY=WINDOW_CENTER_Y;
    float xoff = xpos - lastX;
    float yoff = lastY - ypos; // reversed, since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.0001f;
    xoff *= sensitivity;
    yoff *= sensitivity;
    YAW += xoff;
    PITCH += yoff;
    if (PITCH > 89.0f)
        PITCH = 89.0f;
    if (PITCH < -89.0f)
        PITCH = -89.0f;

    direction.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
    direction.y = sin(glm::radians(PITCH));
    direction.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void window_maximized_callback(GLFWwindow* window, int maximzied) {
    if (maximzied) {
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    } else {
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
    }
}

int main() {
    // Window & Context Setup:
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    std::cout << CURSOR_HOME << CLR_AFTER;
    std::cout.flush();

    // Set callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowSizeCallback(window,framebuffer_size_callback);
    glfwSetWindowMaximizeCallback(window, window_maximized_callback);

    // Debug info
    std::cout << GREEN("SHADER_DIR = ") << BLUE(SHADER_DIR) << std::endl;
    std::cout << GREEN("TEXTURE_DIR = ") << BLUE(TEXTURE_DIR) << std::endl;

    float vertices[] = {
       // positions          // texture coords
       // Face 1
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
       // Face 2
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       // Face 3
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       // Face 4
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       // Face 5
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       // Face 6
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures
    auto tex_container = Texture(GL_TEXTURE_2D, TEXTURE_DIR"/container.jpg", true);
    auto tex_awesomeface = Texture(GL_TEXTURE_2D, TEXTURE_DIR"/awesomeface.png", true);

    // Create shader program
    auto myShaderProg = Shader(SHADER_DIR, "basic");
    myShaderProg.use();
    // Initialize uniforms
    myShaderProg.setInt("texture0", 0);
    myShaderProg.setInt("texture1", 1);

    // Create transforms
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    double deltaTime=0;
    double accDelta=0;// accumulated delta for average frame rate
    double lastTime=0;
    uint d=0;
    std::pair cpos=util::getCursorPos();
    while (!glfwWindowShouldClose(window)) {
        double currTime = glfwGetTime();
        deltaTime = currTime - lastTime;
        float greenValue = (sin(currTime) / 2.0f) + 0.5f;
        // Setup
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, greenValue, 0.3f, 1.0f);
        myShaderProg.use();
        tex_container.activate(GL_TEXTURE0);
        tex_awesomeface.activate(GL_TEXTURE1);
        // Register Keys
        cameraFront = glm::normalize(direction);
        const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraUp;
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraUp;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // Initialize MVP
        glUniformMatrix4fv(myShaderProg.getUniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(myShaderProg.getUniform("view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(myShaderProg.getUniform("proj"), 1, GL_FALSE, glm::value_ptr(proj));

        // Draw
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //model = glm::translate(glm::mat4(1.0f), glm::vec3(0.005f, 0.0f, 0.0f));
        //glUniformMatrix4fv(myShaderProg.getUniform("model"), 1, GL_FALSE, glm::value_ptr(model));
        //glUniformMatrix4fv(myShaderProg.getUniform("view"), 1, GL_FALSE, glm::value_ptr(view));
        //glUniformMatrix4fv(myShaderProg.getUniform("proj"), 1, GL_FALSE, glm::value_ptr(proj));
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        // Print dynamic info
        accDelta += deltaTime;
        if (d >= 12) {// only print every 12 frames
            std::cout << CURSOR_POS(cpos.first, cpos.second) << CLR_AFTER;
            std::cout << "Delta Time: " << accDelta/d << "\n";
            std::cout << "Frame Rate: " << (int)(d/accDelta) << "\n";
            std::cout << "currTime: " << currTime << "\n";
            std::cout.flush();
            accDelta=0;
            d=0;
        };d++;

        // Reset
        glfwSwapBuffers(window);
        glfwPollEvents();
        lastTime = currTime;
    }
    glfwTerminate();
    return 0;
}

