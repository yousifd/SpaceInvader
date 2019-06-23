#version 450 core

out vec4 fragColor;

in vec4 vColor;
in vec2 vTexCoords;

uniform sampler2D tex;

void main() {
	fragColor = texture(tex, vTexCoords);
}