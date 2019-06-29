#include "Missile.h"
#include "Math.h"
#include "Game.h"

Missile::Missile() {
}

Missile::~Missile() {
	game->GetRenderer()->RemoveSprite(&sprite);
}

bool Missile::Init(Game* _game, Actor* _actor, bool _is_enemy) {
	if (!Actor::Init(_game)) {
		printf("Failed to initialize missile actor!\n");
		return false;
	}

	filename = game->GetVariable("Missile", "filename");
	speed = std::stof(game->GetVariable("Missile", "speed"));
	scale_x = std::stof(game->GetVariable("Missile", "scale_x"));
	scale_y = std::stof(game->GetVariable("Missile", "scale_y"));

	if (!sprite.Init(filename.c_str(), this)) {
		printf("Failed to initialize missile sprite!\n");
		return false;
	}

	actor = _actor;
	SetPosition(actor->GetPosition());
	SetScale(Vector3(scale_x, scale_y, 0.f));

	is_enemy = _is_enemy;
	if (is_enemy) {
		SetRotation(PI);
	}

	return true;

}

void Missile::Update(float delta) {
	Vector3 pos = GetPosition();
	glm::vec3 tmp = glm::vec3(pos.x, pos.y, pos.z) + (glm::vec3(0.f, speed * (is_enemy ? -1.f : 1.f), 0.f) * delta);
	SetPosition(Vector3(tmp.x, tmp.y, tmp.z));

	bool reachedEdge = is_enemy ? pos.y <= yMin : pos.y >= yMax;
	if (reachedEdge) {
		game->RemoveMissile(this);
	}
}
