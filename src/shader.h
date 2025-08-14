#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

int load_shader(const char *file_name, char destination[]);

GLuint create_vertex_shader(const char *vertex_shader_source, char info_log[]);

GLuint create_fragment_shader(const char *fragment_shader_source, char info_log[]);

GLuint create_shader_program(GLuint vertex_shader, GLuint fragment_shader, char info_log[]);

#endif // SHADER_H