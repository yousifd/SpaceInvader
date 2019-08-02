#pragma once

#include <glad/glad.h>

class Texture {
public:
	Texture();
	~Texture();

	bool CreateFromFile(const char* filename);
	void CreateFromBuffer(void* buffer, int _width, int _height);
	void Activate();

	int width, height, nrChannels;

private:
	GLuint tex;
};

