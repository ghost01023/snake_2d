#version 330 core

layout (location = 0) in vec3 a_pos;
uniform int shape_type;
uniform vec2 food_position;
uniform float food_size;

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
    color = vec4(0, 0.89, 0, 0.71);
}