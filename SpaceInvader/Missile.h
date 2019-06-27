#pragma once

#include "Actor.h"
#include "Sprite.h"
#include "Shader.h"

class Missile : public Actor {
public:
	Missile();
	~Missile();

	bool Init(Game* _game, Actor* _actor, Shader* shader, bool _isEnemy = false);
	void Update(float delta);

	Sprite sprite;

private:
	float speed = 200.f;
	bool isEnemy = false;

	Actor* actor;
};

