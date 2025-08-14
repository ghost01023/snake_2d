#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_col;
uniform int shape_type;
uniform vec2 food_position;
uniform float food_size;
uniform vec3 in_color;

out vec4 color;

void main() {

    if (shape_type == 1) {
        // triangle

    } else if (shape_type == 2) {
        // circle
    } else {
        // square
    }
    gl_Position = vec4(a_pos.x, a_pos.y, 0.0, 1.0);
    color = vec4(a_col, 0.71);
}