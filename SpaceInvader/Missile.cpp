#include "Missile.h"
#include "Math.h"
#include "Game.h"

Missile::Missile() {
}

Missile::~Missile() {
}

bool Missile::Init(Game* _game, Actor* _actor, Shader* shader, bool _isEnemy) {
	if (!Actor::Init(_game)) {
		printf("Failed to initialize missile actor!\n");
		return false;
	}

	actor = _actor;
	SetPosition(actor->GetPosition());
	SetScale(Vector3(25.f, 40.f, 0.f));

	if (!sprite.Init("missile.png", shader, this)) {
		printf("Failed to initialize missile sprite!\n");
		return false;
	}

	isEnemy = _isEnemy;
	if (isEnemy) {
		SetRotation(PI);
	}

	return true;

}

void Missile::Update(float delta) {
	Vector3 pos = GetPosition();
	glm::vec3 tmp = glm::vec3(pos.x, pos.y, pos.z) + (glm::vec3(0.f, speed * (isEnemy ? -1.f : 1.f), 0.f) * delta);
	SetPosition(Vector3(tmp.x, tmp.y, tmp.z));

	bool reachedEdge = isEnemy ? pos.y <= yMin : pos.y >= yMax;
	if (reachedEdge) {
		game->RemoveMissile(this);
	}
}
