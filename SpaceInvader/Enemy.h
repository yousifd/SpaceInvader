#pragma once

#include "Actor.h"
#include "Missile.h"
#include "Sprite.h"

class Enemy : public Actor {
public:
	Enemy();
	~Enemy();

	bool Init(Game* _game);
	void Update(float delta);

	Sprite& GetSprite() { return sprite; };

private:
	float speed;
	float scale;
	float fire_timer = 0.f;

	Sprite sprite;
	std::string filename;
};

