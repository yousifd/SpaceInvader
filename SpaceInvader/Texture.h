#pragma once

#include <glad/glad.h>

class Texture {
public:
	Texture();
	~Texture();

	bool Init(const char* filename);
	void Activate();

private:
	GLuint tex;
	int width, height, nrChannels;
};

