#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"

Renderer::Renderer() {
}


Renderer::~Renderer() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

bool Renderer::Init(int w, int h) {
	width = w;
	height = h;

	SDL_InitSubSystem(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
	if (!window) {
		printf("Failed to create window!\n");
		return false;
	}

	context = SDL_GL_CreateContext(window);
	if (!context) {
		printf("Failed to create OpenGL context!\n");
		return false;
	}

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		printf("failed to load OpenGL!\n");
		return false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!shader.Init("vertex.glsl", "fragment.glsl")) {
		printf("Failed to init shaders!\n");
		return false;
	}

	// TODO: Move to Camera/Game
	glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f));
	glm::mat4 proj = glm::ortho(-2.f, 2.f, -1.f, 1.f, -1.f, 100.f);

	shader.UploadMatrix(&view, "view");
	shader.UploadMatrix(&proj, "proj");

	return true;
}

void Renderer::Draw() {
	glClearColor(.5f, .5f, .5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (Sprite* sprite : sprites) {
		sprite->Draw();
	}

	SDL_GL_SwapWindow(window);
}

void Renderer::AddSprite(Sprite* sprite) {
	sprites.push_back(sprite);
}
