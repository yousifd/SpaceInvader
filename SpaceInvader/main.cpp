#include <cstdio>

#include "Renderer.h"

void HandleKeyDown(SDL_KeyboardEvent event) {

}

void HandleKeyUp(SDL_KeyboardEvent event) {

}

int main(int argc, char* argv[]) {
	constexpr int w = 1280, h = 720;

	SDL_Init(NULL);

	Renderer renderer;
	if (!renderer.Init(w, h)) {
		printf("Failed to initialize renderer!\n");
		return 1;
	}

	bool running = true;
	float delta = 0;
	unsigned int prevTime = SDL_GetTicks();
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				HandleKeyDown(event.key);
				break;
			case SDL_KEYUP:
				HandleKeyUp(event.key);
				break;
			}
		}

		renderer.Draw();

		delta = (SDL_GetTicks() - prevTime) / 1000.f;
		prevTime = SDL_GetTicks();
	}

	SDL_Quit();

	return 0;
}