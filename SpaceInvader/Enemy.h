#pragma once

#include "Actor.h"
#include "Missile.h"
#include "Sprite.h"

class Enemy : public Actor {
public:
	Enemy();
	~Enemy();

	bool Init(Game* _game, Shader* _shader);
	void Update(float delta);

	Sprite& GetSprite() { return sprite; };

private:
	Sprite sprite;
	float speed = 100.f;
	float scale = 75.f;
	float fireTimer = 0.f;

	Shader* shader;
};

