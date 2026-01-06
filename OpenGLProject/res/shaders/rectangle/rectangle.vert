#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 projection;

void main() {
	gl_Position = projection * model * transform * vec4(aPos, 1.0);
}