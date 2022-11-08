#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "rendering/array_renderer.h"

#include <tuple>

#include "rendering/shader_program.h"

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

    unsigned int vertexShader = CreateShader("res/shaders/shader.vs", GL_VERTEX_SHADER);
    unsigned int fragmentShader = CreateShader("res/shaders/shader.fs", GL_FRAGMENT_SHADER);

    unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    glfwSwapInterval(1);

    GUISystem guiSystem(window);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        if (guiSystem.aSystem)
            guiSystem.aSystem->render();

        guiSystem.update();
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}