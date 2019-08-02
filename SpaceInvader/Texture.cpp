#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"


Texture::Texture() {
}


Texture::~Texture() {
	glDeleteTextures(1, &tex);
}

bool Texture::CreateFromFile(const char* filename) {
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (!data) {
		printf("Failed to load image from %s\n", filename);
		return false;
	}

	CreateFromBuffer(data, width, height);
	stbi_image_free(data);

	//printf("Width: %d\nHeight: %d\n", width, height);

	return true;
}

void Texture::CreateFromBuffer(void* buffer, int _width, int _height) {
	width = _width;
	height = _height;
	glCreateTextures(GL_TEXTURE_2D, 1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Activate() {
	glBindTexture(GL_TEXTURE_2D, tex);
}

