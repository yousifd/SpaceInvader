#include "VertexArray.h"

Vertex::Vertex(float x, float y, float z, float u, float v) {
	pos = Vector3(x, y, z);

	texCoords = Vector2(u, v);
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b, float a, float u, float v) {
	pos = Vector3(x, y, z);

	color = Vector4(r, g, b, a);

	texCoords = Vector2(u, v);
}

VertexArray::VertexArray() {
}


VertexArray::~VertexArray() {
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &vao);
}

bool VertexArray::Init(Vertex* verts, unsigned int _vertCount, unsigned int* indices, int _indexCount, Shader* shader) {
	vertCount = _vertCount;
	indexCount = _indexCount;
	
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex), verts, GL_STREAM_DRAW);

	// Position
	GLuint posLoc = shader->GetAttribLocation("pos");
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(posLoc);

	// Color
	GLuint colorLoc = shader->GetAttribLocation("color");
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
	glEnableVertexAttribArray(colorLoc);

	// Texture Coordinates
	GLuint texCoordsLoc = shader->GetAttribLocation("texCoords");
	glVertexAttribPointer(texCoordsLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, texCoords)));
	glEnableVertexAttribArray(texCoordsLoc);

	//printf("Pos Location %d\nColor location %d\nTexture Coordinates Location %d\n", posLoc, colorLoc, texCoordsLoc);

	// Indices
	glCreateBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STREAM_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

void VertexArray::Activate() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}
