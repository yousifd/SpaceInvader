#pragma once

#if _DEBUG
#pragma comment(lib, "SDL2maind.lib")
#else
#pragma comment(lib, "SDL2main.lib")
#endif

#include <SDL2/SDL.h>

#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	bool Init(int w, int h);
	void Draw();

private:
	SDL_Window* window;
	SDL_GLContext context;

	int width, height;

	//DEBUG
	VertexArray vertexarray;
	Shader shader;
	Texture tex;
};

