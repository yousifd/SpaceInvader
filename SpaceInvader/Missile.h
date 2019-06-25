#pragma once

#include "Actor.h"
#include "Sprite.h"
#include "Shader.h"

class Player;

class Missile : public Actor {
public:
	Missile();
	~Missile();

	bool Init(Game* _game, Player* _player, Shader* shader);
	void Update(float delta);

	Sprite sprite;

private:
	float speed = 200.f;

	Player* player;
};

