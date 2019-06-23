#pragma once

#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"

class Sprite {
public:
	Sprite();
	~Sprite();

	bool Init(const char* filename, Shader* _shader);
	void Draw();

private:
	Texture tex;
	VertexArray verts;
	Shader* shader;
};

