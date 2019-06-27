#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Game.h"

Game::Game() {
	srand(time(NULL));
}

Game::~Game() {
	missiles.clear();
	enemies.clear();
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

	// TODO: Set Variables in a txt file and update values based on it (hot reloading)
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
	float spawnTimer = 0.f;

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

		if (spawnTimer > 2.5f) {
			spawnTimer = 0.f;
			Enemy* enemy = new Enemy();
			enemy->Init(this, &renderer.GetShader());
			enemies.push_back(enemy);
		}

		player.Update(delta);
		for (Missile* missile : missiles) {
			if (missile) {
				missile->Update(delta);
			}
		}
		for (Enemy* enemy : enemies) {
			if (enemy) {
				enemy->Update(delta);
			}
		}
		renderer.Draw();

		spawnTimer += delta;
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
