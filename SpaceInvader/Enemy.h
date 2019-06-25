#pragma once

#include "Actor.h"
#include "Missile.h"
#include "Sprite.h"

class Enemy :
	public Actor {
public:
	Enemy();
	~Enemy();

	bool Init(Game* _game, Shader* _shader);
	bool Update(float delta);

	Sprite& GetSprite() { return sprite; };

private:
	Sprite sprite;

	Shader* shader;
};

