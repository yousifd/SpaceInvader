#pragma once

#include <vector>

#include "Renderer.h"
#include "Player.h"
#include "Missile.h"
#include "Enemy.h"

class Game {
public:
	Game();
	~Game();

	bool Init();
	void Run();

	void AddMissile(Missile* missile);
	void RemoveMissile(Missile* missile);

	Renderer* GetRenderer() { return &renderer; };

private:
	void HandleKeyDown(SDL_KeyboardEvent event);
	void HandleKeyUp(SDL_KeyboardEvent event);

	Renderer renderer;
	Player player;

	std::vector<Missile*> missiles;
	std::vector<Enemy*> enemies;
};