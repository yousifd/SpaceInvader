#pragma once

#if _DEBUG
#pragma comment(lib, "SDL2maind.lib")
#else
#pragma comment(lib, "SDL2main.lib")
#endif

#include <vector>

#include <SDL2/SDL.h>

#include "VertexArray.h"
#include "Shader.h"
#include "Sprite.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	bool Init(int w, int h);
	void Draw();

	Shader& GetShader() { return shader; };
	void AddSprite(Sprite* sprite);

private:
	SDL_Window* window;
	SDL_GLContext context;

	int width, height;

	Shader shader;
	std::vector<Sprite*> sprites;
};

