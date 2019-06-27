#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Game.h"

Game::Game() {
}

Game::~Game() {
	missiles.clear();
	enemies.clear();
	SDL_Quit();
}

bool Game::Init() {
	constexpr int w = 1280, h = 720;

	srand((unsigned int)time(NULL));

	vars.Init("vars.txt");

	SDL_Init(NULL);

	if (!renderer.Init(w, h)) {
		printf("Failed to initialize renderer!\n");
		return false;
	}

	if (!player.Init(this)) {
		printf("Failed to initialize player!\n");
		return false;
	}

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

		if (spawnTimer > std::stof(GetVariable("Game", "spawn_rate"))) {
			spawnTimer = 0.f;
			Enemy* enemy = new Enemy();
			enemy->Init(this);
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
	// TODO: Instead of removing the missile while it is updating
	//	add it to a to_remove list and remove from it every once in a while
	// TODO: Deactiavte missile actor when it is added to the to_remove list
	auto it = std::find(missiles.begin(), missiles.end(), missile);
	if (it != missiles.end()) {
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
