#include <iostream>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Additional 3rd-party libs
#include "glad/gl.h"
#include "GLFW/glfw3.h"


// User defined libs
#include "window.h"
#include "shader.h"
#include "food.h"


bool food_generated = false;


void process_input(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	} else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		cout << "Receiving input of 0" << endl;
		if (!food_generated) {
			food new_food = generate_food(TRIANGLE);
			food_generated = true;
			print_food_details(new_food);
		}
	} else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		cout << "Food was eaten!" << endl;
		food_generated = false;
	}
}


GLuint create_array_buffer_object(GLfloat vertices[], int length, GLenum draw_type, int attribute_sequence[], int sequence_length) {

	//attrib_sequence = [3, 3], seq_len = 2
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// cout << endl;
	// cout << triangle_food.center[0] << "\t" << triangle_food.center[1] << endl;
	// cout << endl;
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length, vertices, draw_type);
	
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, length * sizeof(float), (void *)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);
	int sequence_iter = 0;
	for (int i = 0; i < sequence_length; i++) {
		printf("i: %d, attribute_sequence[i]: %d, length * sizeof(float): %lu, sequence_iter * sizeof(float): %lu\n", i, attribute_sequence[i], length * sizeof(float), sequence_iter * sizeof(float));
		glVertexAttribPointer(i, attribute_sequence[i], GL_FLOAT, GL_FALSE, length * sizeof(float), (void *)(sequence_iter * sizeof(float)));
		sequence_iter += attribute_sequence[i];
		glEnableVertexAttribArray(i);
	}
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
	glGenVertexArrays(2, VAO);
	// glBindVertexArray(VAO[0]);

	
	
	// glGenBuffers(1, &VBO);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	// glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), triangle_food.food_coords, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	// glEnableVertexAttribArray(0);
	// print_food_details(triangle_food);

	// test center of triangle
	// GLuint VBO_point;
	
	// glGenBuffers(1, &VBO_point);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO_point);
	// triangle_food.center[2] = 1.0f;
	// cout << endl;
	// cout << triangle_food.center[0] << "\t" << triangle_food.center[1] << endl;
	// cout << endl;
	// glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3, triangle_food.center, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	// glEnableVertexAttribArray(0);

	const int ebo_triangle_indices[] = {0, 1, 2};
	const int ebo_square_indices[] = {0, 1, 2, 1, 2, 3};
	GLuint EBO_triangle, EBO_square;
	glGenBuffers(1, &EBO_triangle);
	glGenBuffers(1, &EBO_square);
	

	glPointSize(10.0f);
	
	srand(time(NULL));

	food new_food;

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.63, 0.4, 0.86, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_program);
		if (!food_generated) {

			//FOOD
			glBindVertexArray(VAO[0]);
			int food_type = rand() % 3;
			if (food_type == 0) {
				new_food = generate_food(TRIANGLE);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_triangle);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ebo_triangle_indices), ebo_triangle_indices, GL_STATIC_DRAW);
			} else {
				new_food = generate_food(SQUARE);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_square);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ebo_square_indices), ebo_square_indices, GL_STATIC_DRAW);

			}
			int attrib_seq[] = {3, 3};

			cout << "food coords are " << endl;
			for (int i = 0; i < new_food.size; i++) {
				cout << new_food.food_coords[i] << "\t";
			}
			cout << endl;
			cout << "will create with size " << new_food.size << endl;
			create_array_buffer_object(new_food.food_coords, new_food.size, GL_STATIC_DRAW, attrib_seq, 2);
			

			//CENTER OF FOOD
			
			glBindVertexArray(VAO[1]);
			int attrib_seq_2[] = {1};
			create_array_buffer_object(new_food.center, new_food.size, GL_STATIC_DRAW, attrib_seq_2, 1);
			food_generated = true;
			// glDrawArrays(GL_POINTS, 0, 1);

		}
		else {
			glBindVertexArray(VAO[0]);
			glDrawElements(GL_TRIANGLES, new_food.shape == TRIANGLE ? 3 : 6, GL_UNSIGNED_INT, 0);
			// glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_POINTS, 0, 1);
		}
		
		glfwSwapBuffers(window);
		process_input(window);
		glfwPollEvents();
	}
	return 0;

}
