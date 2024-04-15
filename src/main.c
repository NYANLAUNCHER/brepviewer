// vim: foldmethod=marker
#include <stdlib.h>
#include <stdio.h>
// OpenGL Stuffs
#include <GL/gl3w.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
// Custom
#include "util.h"
#include "brep.h"
// STB
#define STB_IMAGE_IMPLEMENTATION
#define STB_FAILURE_USERMSG
#include "stb_image.h"

int main(int argc, char** argv) {
    // Initialization: {{{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "brepviewer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //}}}

    // Data: {{{
    float vertices[] = {
    };
    float indices[] = {
    };
    unsigned int VBO, VAO, EBO;
    // }}}

    while (!glfwWindowShouldClase(window)) {
        // Update
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw

        // Render
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
