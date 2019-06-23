#pragma once

#include "Renderer.h"
#include "Player.h"

class Game {
public:
	Game();
	~Game();

	bool Init();
	void Run();

private:
	void HandleKeyDown(SDL_KeyboardEvent event);
	void HandleKeyUp(SDL_KeyboardEvent event);

	Renderer renderer;
	Player player;
};