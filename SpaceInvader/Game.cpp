#include <algorithm>
#include <cstdlib>
#include <ctime>

#include <windows.h>

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

	vars.Init("vars\\vars.txt");

	SDL_Init(NULL);

	if (!renderer.Init(w, h)) {
		printf("Failed to initialize renderer!\n");
		return false;
	}

	if (!font.Init(w, h)) {

	}


	if (!player.Init(this)) {
		printf("Failed to initialize player!\n");
		return false;
	}


	// TODO: Text
	// TODO: Sound
	// TODO: Particle Effects
	// TODO: Camera?

	return true;
}

DWORD WINAPI CheckForChange(LPVOID lpParam) {
	VariableManager* vars = (VariableManager*)lpParam;
	vars->CheckForChange();

	return 0;
}

void Game::Run() {
	bool running = true;
	float delta = 0;
	unsigned int prevTime = SDL_GetTicks();
	float spawnTimer = 0.f;

	HANDLE h = CreateThread(NULL, 0, CheckForChange, &vars, 0, NULL);
	if (!h) {
		printf("Failed to create thread!\n");
		return;
	}

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

		for (auto* missile : missilesToDelete) {
			delete missile;
		}
		missilesToDelete.clear();

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

	CloseHandle(h);
}

void Game::AddMissile(Missile* missile) {
	missiles.push_back(missile);
}

void Game::RemoveMissile(Missile* missile) {
	auto it = std::find(missiles.begin(), missiles.end(), missile);
	if (it != missiles.end()) {
		missiles.erase(it);
	}
	missilesToDelete.push_back(missile);
}

void Game::HandleKeyDown(SDL_KeyboardEvent event) {
	player.HandleKeyDown(event);
}

void Game::HandleKeyUp(SDL_KeyboardEvent event) {
	player.HandleKeyUp(event);
}
