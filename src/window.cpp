#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;


void glfwFrameBufferSizeCallback(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width - 400, height - 400);
}


GLFWwindow *init_window() {
	cout << "Attempting to initialize and launch GLFWWindow object" << endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWmonitor *primary_monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *video_mode = glfwGetVideoMode(primary_monitor);
	GLFWwindow *window = glfwCreateWindow(video_mode->width, video_mode->height, "snake_2d", NULL, NULL);

	if (!window) {
		cout << "FAILED TO CREATE GLFWwindow" << endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		cout << "Failed to initialize glad" << endl;
		glfwTerminate();
		return NULL;
	}

	glViewport(0, 0, video_mode->width, video_mode->height);
	

	glfwSetFramebufferSizeCallback(window, glfwFrameBufferSizeCallback);
	cout << "Hello, Snake World!" << endl;
	return window;
}
