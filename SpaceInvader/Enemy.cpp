#include <cstdlib>

#include "Enemy.h"
#include "Math.h"
#include "Game.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
}


bool Enemy::Init(Game* _game, Shader* _shader) {
	if (!Actor::Init(_game)) {
		printf("Failed to initialize Enemy's actor class!\n");
		return false;
	}

	shader = _shader;
	if (!sprite.Init("ship.png", shader, this)) {
		printf("Failed to initialize Enemy's sprite!\n");
		return false;
	}

	float MinSpawnPoint = 150.f;

	float yPos = ((float)rand() / (float)RAND_MAX) * yMax * (rand() % 2 == 0 ? -1 : 1);
	yPos = yPos < yMax - MinSpawnPoint? yMax - MinSpawnPoint : yPos;
	float xPos = ((float)rand() / (float)RAND_MAX) * xMax * (rand() % 2 == 0 ? -1 : 1);

	SetPosition(Vector3(xPos, yPos, 0.f));
	SetScale(Vector3(scale, scale, 0.f));
	SetRotation(PI);

	return true;
}

void Enemy::Update(float delta) {
	Vector3 pos = GetPosition();
	velocity.x = (float)rand() / (float)RAND_MAX * speed * (rand() % 2 == 0 ? -1 : 1);
	velocity.y = ((float)rand() / (float)RAND_MAX) * -speed;
	//printf("New Velocity x: %f, y: %f\n", velocity.x, velocity.y);
	glm::vec3 tmp = glm::vec3(pos.x, pos.y, pos.z) + (glm::vec3(velocity.x, velocity.y, 0.f) * delta);
	SetPosition(Vector3(tmp.x, tmp.y, tmp.z));

	fireTimer += delta;
	if (fireTimer >= 2.5f) {
		Missile* missile = new Missile();
		missile->Init(game, this, shader, true);
		game->AddMissile(missile);
		fireTimer = 0.f;
	}
}