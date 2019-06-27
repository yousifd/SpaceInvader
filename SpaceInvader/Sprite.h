#pragma once

#include "Texture.h"
#include "Shader.h"
#include "Actor.h"

class Sprite {
public:
	Sprite();
	~Sprite();

	bool Init(const char* filename, Actor* _owner);
	void UploadUniforms(Shader* shader);

	Texture tex;

private:
	Actor* owner;
};

