#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "Actor.h"
#include "Sprite.h"
#include "Shader.h"
#include "Missile.h"

class Player : public Actor {
public:
	Player();
	~Player();

	bool Init(Shader* shader);
	void Update(float delta);

	Sprite& GetSprite() { return sprite; };

	void HandleKeyDown(SDL_KeyboardEvent event);
	void HandleKeyUp(SDL_KeyboardEvent event);

private:
	Sprite sprite;
	bool is_pressed[2];
	float speed = 2.f;

	std::vector<Missile*> missiles;
};

