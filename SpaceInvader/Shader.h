#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.h"

class Shader {
public:
	Shader();
	~Shader();

	bool Init(const char* vertex, const char* fragment);
	GLuint GetAttribLocation(const char* name);
	void Activate();
	void UploadTexture(Texture* tex, const char* name, GLuint unit);
	void UploadMatrix(glm::mat4* mat, const char* name);

private:
	std::string ReadFile(const char* filename);
	bool ShaderStatus(GLuint shader);
	bool ProgramStatus(GLuint program);

	GLuint vertexShader, fragmentShader, program;
};

