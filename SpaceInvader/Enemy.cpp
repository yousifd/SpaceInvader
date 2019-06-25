#include "Enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
}


bool Enemy::Init(Game* _game, Shader* _shader) {
	if (!Actor::Init(game)) {
		printf("Failed to initialize Enemy's actor class!\n");
		return false;
	}

	shader = _shader;
	if (!sprite.Init("enemy.png", shader, this)) {
		printf("Failed to initialize Enemy's sprite!\n");
		return false;
	}

	return true;
}

bool Enemy::Update(float delta) {
	// TODO: Move
	// TODO: Shoot at player
}