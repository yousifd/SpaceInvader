#pragma once

#include <vector>
#include <map>
#include <string>
#include <atomic>

#include <SDL2/SDL.h>

#include "Sprite.h"
#include "Missile.h"
#include "CollisionManager.h"

class Game;
class Actor;

class Player : public Actor {
public:
	Player();
	~Player();

	bool Init(Game* _game);
	void Update(float delta);

	void VariableUpdateCallback(const std::map<std::string, std::string>& kvs);

	void HandleKeyDown(SDL_KeyboardEvent event);
	void HandleKeyUp(SDL_KeyboardEvent event);

	const Sprite& GetSprite() { return sprite; };

private:
	Sprite sprite;
	Collider collider;
	bool is_pressed[3] = { false };
	float speed;
	float scalarScale;
	float fire_wait_time;
	float fire_timer;

	std::string filename;
	std::atomic<bool> updateSprite;
};

