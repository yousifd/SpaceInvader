#pragma once

#include <glad/glad.h>

#include "Math.h"
#include "Shader.h"

struct Vertex {
	Vector3 pos;
	Vector4 color;
	Vector2 texCoords;

	Vertex(float x, float y, float z, float u, float v);
	Vertex(float x, float y, float z, float r, float g, float b, float a, float u, float v);
};

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	bool Init(Vertex* verts, unsigned int vertCount, unsigned int* indices, int indexCount, Shader* shader);
	void Activate();

	unsigned int GetIndexCount() { return indexCount; };

private:
	GLuint vao, vbo, ebo;
	unsigned int vertCount, indexCount;
};

