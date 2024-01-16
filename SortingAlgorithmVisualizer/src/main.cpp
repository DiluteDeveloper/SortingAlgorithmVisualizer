#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <tuple>

#include "rendering/2D/renderer.h"

#include "gui/gui_system.h"

int main(void) {

    if (!glfwInit()) return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;

    window = glfwCreateWindow(1280, 720, "Sorting Algorithm Visualizer", NULL, NULL);
    if (!window) return -1;

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) return -1;

    glfwSwapInterval(0);

    Renderer2D r2D;
    GUISystem guiSystem(window);

    double previousTime = glfwGetTime();
    int frameCount = 0;

    bool guiHide = false;
    bool notHeld = true;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        r2D.renderArrayMesh(guiSystem.aSystem.mesh);

        if (glfwGetKey(window, GLFW_KEY_H)) {
            if (notHeld) {
                guiHide = !guiHide;
                notHeld = false;
            }
        }
        else notHeld = true;
            
        if (!guiHide)
            guiSystem.update();
          
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}