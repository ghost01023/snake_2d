#ifndef WINDOW_H
#define WINDOW_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

void glfwFrameBufferSizeCallback(GLFWwindow * window, int width, int height);

GLFWwindow *init_window();


#endif // WINDOW_H