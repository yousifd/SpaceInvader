#pragma once

#include "Actor.h"
#include "Sprite.h"

class Missile : public Actor {
public:
	Missile();
	~Missile();

	bool Init(Game* _game, Actor* _actor, bool _is_enemy = false);
	void Update(float delta);

	Sprite sprite;

private:
	float speed;
	float scale_x, scale_y;
	bool is_enemy = false;

	Actor* actor;
	std::string filename;
};

