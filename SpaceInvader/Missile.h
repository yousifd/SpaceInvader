#pragma once

#include "Actor.h"
#include "Sprite.h"

class Missile : public Actor {
public:
	Missile();
	~Missile();

	// TODO:
	void Update();

private:
	Sprite sprite;
	float speed = 0.1f;
};

