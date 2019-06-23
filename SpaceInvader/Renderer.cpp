#include <glad/glad.h>

#include "Renderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Sprite.h"

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

	// DEBUGING
	Sprite sprite;
	sprite.Init("ship.png", &shader);

	return true;
}

void Renderer::Draw() {
	glClearColor(.5f, .5f, .5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);


	glDrawElements(GL_TRIANGLES, vertexarray.GetIndexCount(), GL_UNSIGNED_INT, nullptr);

	SDL_GL_SwapWindow(window);
}
