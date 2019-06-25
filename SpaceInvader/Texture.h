#pragma once

#include <glad/glad.h>

class Texture {
public:
	Texture();
	~Texture();

	bool Init(const char* filename);
	void Activate();

	int width, height, nrChannels;

private:
	GLuint tex;
};

