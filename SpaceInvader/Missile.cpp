#include "Missile.h"
#include "Player.h"
#include "Math.h"
#include "Game.h"

Missile::Missile() {
}

Missile::~Missile() {
}

bool Missile::Init(Game* _game, Player* _player, Shader* shader) {
	if (!Actor::Init(_game)) {
		printf("Failed to initialize missile actor!\n");
		return false;
	}

	player = _player;
	SetPosition(player->GetPosition());
	SetScale(Vector3(25.f, 40.f, 0.f));

	if (!sprite.Init("missile.png", shader, this)) {
		printf("Failed to initialize missile sprite!\n");
		return false;
	}

	return true;

}

void Missile::Update(float delta) {
	Vector3 pos = GetPosition();
	glm::vec3 tmp = glm::vec3(pos.x, pos.y, pos.z) + (glm::vec3(0.f, speed, 0.f) * delta);
	SetPosition(Vector3(tmp.x, tmp.y, tmp.z));

	if (pos.y >= yMax) {
		game->RemoveMissile(this);
	}
}
