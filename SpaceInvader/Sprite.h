#pragma once

#include "Texture.h"
#include "Shader.h"
#include "Actor.h"

class Sprite {
public:
	Sprite();
	~Sprite();

	bool Init(const char* filename, Shader* _shader, Actor* _owner);
	void UploadUniforms();

	Texture tex;

private:
	Shader* shader;
	Actor* owner;
};

