#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "Sprite.h"
#include "Shader.h"
#include "Missile.h"

class Game;
class Actor;

class Player : public Actor {
public:
	Player();
	~Player();

	bool Init(Game* _game, Shader* shader);
	void Update(float delta);

	void HandleKeyDown(SDL_KeyboardEvent event);
	void HandleKeyUp(SDL_KeyboardEvent event);

	Sprite& GetSprite() { return sprite; };

private:
	Sprite sprite;
	bool is_pressed[3] = { false };
	float speed = 300.f;
	float scale = 75.f;
	const float fire_wait_time = 1.f;
	float fire_timer = fire_wait_time;

	Shader* shader;
};

