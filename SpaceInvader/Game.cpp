#include <algorithm>

#include "Game.h"

Game::Game() {
}

Game::~Game() {
	missiles.clear();
	SDL_Quit();
}

bool Game::Init() {
	constexpr int w = 1280, h = 720;

	SDL_Init(NULL);

	if (!renderer.Init(w, h)) {
		printf("Failed to initialize renderer!\n");
		return false;
	}

	if (!player.Init(this, &renderer.GetShader())) {
		printf("Failed to initialize player!\n");
		return false;
	}

	// TODO: Enemies
	// TODO: Collision Detection
	// TODO: Sound
	// TODO: Particle Effects
	// TODO: Camera?

	return true;
}

void Game::Run() {
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

		player.Update(delta);
		for (Missile* missile : missiles) {
			if (missile) {
				missile->Update(delta);
			}
		}
		renderer.Draw();

		delta = (SDL_GetTicks() - prevTime) / 1000.f;
		prevTime = SDL_GetTicks();
	}
}

void Game::AddMissile(Missile* missile) {
	missiles.push_back(missile);
}

void Game::RemoveMissile(Missile* missile) {
	auto it = std::find(missiles.begin(), missiles.end(), missile);
	if (it != missiles.end()) {
		printf("Removed Missile!");
		missiles.erase(it);
	}
	renderer.RemoveSprite(&missile->sprite);
	delete missile;
}

void Game::HandleKeyDown(SDL_KeyboardEvent event) {
	player.HandleKeyDown(event);
}

void Game::HandleKeyUp(SDL_KeyboardEvent event) {
	player.HandleKeyUp(event);
}
