#include <iostream>
#include <filesystem>
#include <string.h>

using namespace std;

#include <glad/gl.h>

int load_shader(const char *file_name, char destination[]) {
    char file_relative_path[25];
    file_relative_path[0] = '\0';
    destination[0] = '\0';
    strcat(file_relative_path, "../shaders/");
    strcat(file_relative_path, file_name);
    cout << "opening " << file_relative_path << endl;
    char shader_source_buffer[10];
    FILE *fptr = fopen(file_relative_path, "r");

    if (!fptr) {
        cout << "Failed to open " << file_name << " shader" << endl;
        return 0;
    }
    while (fgets(shader_source_buffer, 10, fptr)) {
        strcat(destination, shader_source_buffer);
    }
    return 1;
}


unsigned int create_vertex_shader(const char *vertex_shader_source, char info_log[]) {
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    int success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        cout << "ERROR::COMPILE::VERTEX_SHADER" << endl;
        glGetShaderInfoLog(vertex_shader, 1024, NULL, info_log);
        cout << info_log << endl;
        return 0;
    }
    cout << "Vertex shader compiled successfully!" << endl;
    return vertex_shader;
}


unsigned int create_fragment_shader(const char *fragment_shader_source, char info_log[]) {
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    int success;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        cout << "ERROR::COMPILE::FRAGMENT_SHADER" << endl;
        glGetShaderInfoLog(fragment_shader, 1024, NULL, info_log);
        cout << info_log << endl;
        return 0;
    }

    cout << "Fragment shader compiled successfully!" << endl;
    return fragment_shader;
}


GLuint create_shader_program(unsigned int vertex_shader, GLuint fragment_shader, char info_log[]) {
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        cout << "ERROR::LINK::SHADER_PROGRAM" << endl;
        glGetProgramInfoLog(shader_program, 1024, NULL, info_log);
        cout << info_log << endl;
        return 0;
    }
    cout << "Shader program was linked successfully!" << endl;
    return shader_program;
}