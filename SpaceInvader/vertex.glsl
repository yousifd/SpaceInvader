#version 450 core

in vec3 pos;
in vec4 color;
in vec2 texCoords;

out vec4 vColor;
out vec2 vTexCoords;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
	gl_Position = proj * view * model * vec4(pos, 1.0);

	vColor = color;
	vTexCoords = texCoords;
}