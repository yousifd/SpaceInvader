#pragma once

#include <vector>
#include <map>
#include <string>

#include <SDL2/SDL.h>

#include "Sprite.h"
#include "Missile.h"

class Game;
class Actor;

class Player : public Actor {
public:
	Player();
	~Player();

	bool Init(Game* _game);
	void Update(float delta);

	void VariableUpdateCallback(std::map<std::string, std::string> kvs);

	void HandleKeyDown(SDL_KeyboardEvent event);
	void HandleKeyUp(SDL_KeyboardEvent event);

	Sprite& GetSprite() { return sprite; };

private:
	Sprite sprite;
	bool is_pressed[3] = { false };
	float speed;
	float scale;
	float fire_wait_time;
	float fire_timer;

	std::string filename;
};

