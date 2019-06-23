#pragma once

#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Actor.h"

class Sprite {
public:
	Sprite();
	~Sprite();

	bool Init(const char* filename, Shader* _shader, Actor* _owner);
	void Draw();

private:
	Texture tex;
	VertexArray verts;
	Shader* shader;
	Actor* owner;
};

