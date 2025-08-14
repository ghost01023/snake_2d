#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

// Additional 3rd-party libs
#include "glad/gl.h"
#include "GLFW/glfw3.h"


// User defined libs
#include "window.h"
#include "shader.h"
#include "food.h"



void process_input(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	} else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		cout << "Receiving input of 0" << endl;
		food new_food = generate_food(TRIANGLE);
		print_food_details(new_food);
	}
}

GLuint create_array_buffer_object(GLfloat vertices[], int length, GLenum draw_type) {
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// cout << endl;
	// cout << triangle_food.center[0] << "\t" << triangle_food.center[1] << endl;
	// cout << endl;
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length, vertices, draw_type);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	return VBO;
}

int main() {

	GLFWwindow *window = init_window();
	if (!window) {
		return EXIT_FAILURE;
	}

	int success;
	// LOAD VERTEX AND FRAGMENT SHADER FILE

	char vertex_shader_source[1000];
	success = load_shader("vertex.vert", vertex_shader_source);
	if (!success)
	{
		return EXIT_FAILURE;
	}
	char fragment_shader_source[1000];
	success = load_shader("fragment.frag", fragment_shader_source);
	if (!success)
	{
		return EXIT_FAILURE;
	}

	// MAINLY FUNCTIONS AS AN ERROR LOG
	char info_log[1024];
	unsigned int vertex_shader = create_vertex_shader(vertex_shader_source, info_log);
	if (!vertex_shader)
	{
		return EXIT_FAILURE;
	}
	unsigned int fragment_shader = create_fragment_shader(fragment_shader_source, info_log);
	if (!fragment_shader)
	{
		return EXIT_FAILURE;
	}
	unsigned int shader_program = create_shader_program(vertex_shader, fragment_shader, info_log);
	if (!shader_program)
	{
		return EXIT_FAILURE;
	}

	// char fragment_shaderYellowSource[1000];
	// success = loadShader("fragment_yellow.frag", fragment_shaderYellowSource);
	// if (!success)
	// {
	// 	return EXIT_FAILURE;
	// }
	// unsigned int fragment_shaderYellow = create_fragment_shader(fragment_shaderYellowSource, infoLog);
	// unsigned int shaderProgramYellow = createShaderProgram(vertex_shader, fragment_shaderYellow, infoLog);
	// checkOpenGLError("After createShaderProgram for yellowfragment_shader");
	// if (!shaderProgramYellow)
	// {
	// 	return EXIT_FAILURE;
	// }

	// FREE MEMORY AFTER SHADER SOURCE USE
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	GLuint VAO[2];
	glGenVertexArrays(1, &VAO[0]);
	glBindVertexArray(VAO[0]);
	
	// glGenBuffers(1, &VBO);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	food triangle_food = generate_food(TRIANGLE);
	create_array_buffer_object(triangle_food.food_coords, 9, GL_STATIC_DRAW);
	// glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), triangle_food.food_coords, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	// glEnableVertexAttribArray(0);
	print_food_details(triangle_food);

	// test center of triangle
	// GLuint VBO_point;
	glGenVertexArrays(1, &VAO[1]);
	glBindVertexArray(VAO[1]);
	create_array_buffer_object(triangle_food.center, 3, GL_STATIC_DRAW);
	// glGenBuffers(1, &VBO_point);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO_point);
	// triangle_food.center[2] = 1.0f;
	// cout << endl;
	// cout << triangle_food.center[0] << "\t" << triangle_food.center[1] << endl;
	// cout << endl;
	// glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3, triangle_food.center, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	// glEnableVertexAttribArray(0);

	glPointSize(10.0f);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.63, 0.4, 0.86, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_program);
		glBindVertexArray(VAO[0]);
		// glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(VAO[1]);
		// glBindBuffer(GL_ARRAY_BUFFER, VBO_point);
		glDrawArrays(GL_POINTS, 0, 1);
		glfwSwapBuffers(window);
		process_input(window);
		glfwPollEvents();
	}
	return 0;

}
