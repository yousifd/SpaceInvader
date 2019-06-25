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
#include "VertexArray.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	bool Init(int w, int h);
	void Draw();

	Shader& GetShader() { return shader; };
	void AddSprite(Sprite* sprite);
	void RemoveSprite(Sprite* sprite);

	int width, height;

private:
	SDL_Window* window;
	SDL_GLContext context;

	Shader shader;
	std::vector<Sprite*> sprites;
	VertexArray verts;
};

