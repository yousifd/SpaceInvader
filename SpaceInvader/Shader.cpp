#include <sstream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

Shader::Shader() {
}

Shader::~Shader() {
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteProgram(program);
}

bool Shader::Init(const char* vertex, const char* fragment) {
	std::string vertexSourceStr = ReadFile(vertex);
	if (vertexSourceStr.size() == 0) {
		printf("Failed to load vertex shader source!\n");
		return false;
	}
	const char* vertexSource = vertexSourceStr.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	if (!ShaderStatus(vertexShader)) {
		printf("Failed to compile vertex shader!\n");
		return false;
	}

	std::string fragmentSourceStr = ReadFile(fragment);
	if (fragmentSourceStr.size() == 0) {
		printf("Failed to load fragment shader source!\n");
		return false;
	}
	const char* fragmentSource = fragmentSourceStr.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	if (!ShaderStatus(fragmentShader)) {
		printf("Failed to compile fragment shader!\n");
		return false;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	if (!ProgramStatus(program)) {
		printf("Failed to link shader program!\n");
		return false;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}

GLuint Shader::GetAttribLocation(const char* name) {
	return glGetAttribLocation(program, name);
}

void Shader::Activate() {
	glUseProgram(program);
}

void Shader::UploadTexture(Texture* tex, const char* name, GLuint unit) {
	Activate();
	glActiveTexture(unit);
	tex->Activate();

	GLuint samplerLoc = glGetUniformLocation(program, name);
	glUniform1i(samplerLoc, unit);

	//printf("Uploaded texture to %d\n", samplerLoc);
}

void Shader::UploadMatrix(glm::mat4* mat, const char* name) {
	Activate();
	GLuint matLoc = glGetUniformLocation(program, name);
	glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(*mat));
}

std::string Shader::ReadFile(const char* filename) {
	std::stringstream ss;
	std::ifstream file(filename);
	ss << file.rdbuf();

	//printf("Shader %s:\n%s\n", filename, ss.str().c_str());

	file.close();
	return ss.str();
}

bool Shader::ShaderStatus(GLuint shader) {
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("Failed to compile shader (%d): %s\n", shader, infoLog);
	}

	return success;
}

bool Shader::ProgramStatus(GLuint prog) {
	int success;
	glGetProgramiv(prog, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(prog, 512, nullptr, infoLog);
		printf("Failed to link program (%d): %s\n", prog, infoLog);
	}

	return success;
}
